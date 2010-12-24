/*
 * The interface of dynamic compiled mode for ppc simulation
 *
 * 08/22/2010 Michael.Kang (blackfin.kang@gmail.com)
 */
#include <llvm/LLVMContext.h>
#include <llvm/Type.h>
#include <llvm/Function.h>
#include <llvm/Module.h>
#include <llvm/Constant.h>

#include <skyeye_dyncom.h>
#include <skyeye_types.h>
#include <skyeye_obj.h>
#include <skyeye.h>
#include <dyncom/dyncom_llvm.h>

#include "ppc_cpu.h"
#include "ppc_mmu.h"
#include "ppc_dyncom.h"
#include "ppc_dyncom_run.h"

e500_core_t* get_core_from_dyncom_cpu(cpu_t* cpu){
	e500_core_t* core = (e500_core_t*)get_cast_conf_obj(cpu->cpu_data, "e500_core_t");
	return core;
}

/* physical register for powerpc archtecture */
static void arch_powerpc_init(cpu_t *cpu, cpu_archinfo_t *info, cpu_archrf_t *rf)
{
	// Basic Information
	info->name = "powerpc";
	info->full_name = "powerpc_common";

	// This architecture is biendian, accept whatever the
	// client wants, override other flags.
	info->common_flags &= CPU_FLAG_ENDIAN_MASK;

	info->delay_slots = 0;
	// The byte size is 8bits.
	// The word size is 32bits.
	// The float size is 64bits.
	// The address size is 32bits.
	info->byte_size = 8;
	info->word_size = 32;
	info->float_size = 64;
	info->address_size = 32;
	// There are 16 32-bit GPRs
	info->register_count[CPU_REG_GPR] = MAX_REGNUM;
	info->register_size[CPU_REG_GPR] = info->word_size;
	// There is also 1 extra register to handle PSR.
	//info->register_count[CPU_REG_XR] = PPC_XR_SIZE;
	info->register_count[CPU_REG_XR] = 0;
	info->register_size[CPU_REG_XR] = 32;
	cpu->redirection = false;
}

static void
arch_powerpc_done(cpu_t *cpu)
{
	//free(cpu->rf.grf);
}

static addr_t
arch_powerpc_get_pc(cpu_t *cpu, void *reg)
{
	e500_core_t* core = (e500_core_t*)get_cast_conf_obj(cpu->cpu_data, "e500_core_t");

	return core->phys_pc;
	//return ((reg_powerpc_t *)reg)->pc;
}

static uint64_t
arch_powerpc_get_psr(cpu_t *, void *reg)
{
	return 0;
}

static int
arch_powerpc_get_reg(cpu_t *cpu, void *reg, unsigned reg_no, uint64_t *value)
{
	return (0);
}

static int arch_powerpc_disasm_instr(cpu_t *cpu, addr_t pc, char* line, unsigned int max_line){
	return 0;
}
static int arch_powerpc_translate_loop_helper(cpu_t *cpu, addr_t pc, BasicBlock *bb_ret, BasicBlock *bb_next, BasicBlock *bb, BasicBlock *bb_zol_cond){
	return 0;
}
static arch_func_t powerpc_arch_func = {
	arch_powerpc_init,
	arch_powerpc_done,
	arch_powerpc_get_pc,
	NULL,
	NULL,
	arch_powerpc_tag_instr,
	arch_powerpc_disasm_instr,
	arch_powerpc_translate_cond,
	arch_powerpc_translate_instr,
        arch_powerpc_translate_loop_helper,
	// idbg support
	arch_powerpc_get_psr,
	arch_powerpc_get_reg,
	NULL
};

/**
* @brief Place all the powerpc debug output here.
*
* @param cpu the instance of cpu_t
*/
static void ppc_debug_func(cpu_t* cpu){
	printf("In %s, phys_pc=0x%x\n", __FUNCTION__, *(addr_t*)cpu->rf.phys_pc);
	return;
}
void ppc_dyncom_init(e500_core_t* core){
	cpu_t* cpu = cpu_new(0, 0, powerpc_arch_func);
	cpu->cpu_data = get_conf_obj_by_cast(core, "e500_core_t");
	/* Initilize different register set for different core */
	cpu->rf.pc = &core->pc;
	cpu->rf.phys_pc = &core->phys_pc;
	cpu->rf.grf = core->gpr;
	cpu_set_flags_debug(cpu, 0
                | CPU_DEBUG_PRINT_IR
                | CPU_DEBUG_LOG
                );
	cpu->debug_func = ppc_debug_func;
	core->dyncom_cpu = get_conf_obj_by_cast(cpu, "cpu_t");
	return;
}

/**
* @brief Debug function that will be called in every instruction execution, print the cpu state
*
* @param cpu the cpu_t instance
*/
static void
debug_function(cpu_t *cpu) {
	return;
}
void ppc_dyncom_run(cpu_t* cpu){
	e500_core_t* core = (e500_core_t*)get_cast_conf_obj(cpu->cpu_data, "e500_core_t");
	addr_t phys_pc = 0;
	if(ppc_effective_to_physical(core, core->pc, PPC_MMU_CODE, &phys_pc) != PPC_MMU_OK){
		/* we donot allow mmu exception in tagging state */
		fprintf(stderr, "In %s, can not translate the pc 0x%x\n", __FUNCTION__, core->pc);
		exit(-1);
	}
	printf("In %s,pc=0x%x,phys_pc=0x%x\n", __FUNCTION__, core->pc, phys_pc);
	core->phys_pc = phys_pc;
	cpu->dyncom_engine->code_start = phys_pc;
        cpu->dyncom_engine->code_end = get_end_of_page(phys_pc);
        cpu->dyncom_engine->code_entry = phys_pc;

	int rc = cpu_run(cpu, debug_function);
	switch (rc) {   
                case JIT_RETURN_NOERR: /* JIT code wants us to end execution */
                        break;  
                case JIT_RETURN_SINGLESTEP:
                case JIT_RETURN_FUNCNOTFOUND:
			printf("In %s, function not found at 0x%x\n", __FUNCTION__, core->phys_pc);
                        cpu_tag(cpu, core->phys_pc);
                        cpu->dyncom_engine->functions = 0;
                        cpu_translate(cpu);
		 /*
                  *If singlestep,we run it here,otherwise,break.
                  */
                        if (cpu->dyncom_engine->flags_debug & CPU_DEBUG_SINGLESTEP){
                                rc = cpu_run(cpu, debug_function);
                                if(rc != JIT_RETURN_TRAP)
                                        break;
                        }
                        else
                                break;
		case JIT_RETURN_TRAP:
			break;
		default:
                        fprintf(stderr, "unknown return code: %d\n", rc);
			skyeye_exit(-1);
        }// switch (rc)
	return;
}

void ppc_dyncom_stop(){
}

void ppc_dyncom_fini(){
}
