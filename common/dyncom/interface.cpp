/*
 * libcpu: interface.cpp
 *
 * This is the interface to the client.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llvm/Analysis/Verifier.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/LinkAllPasses.h"
#include "llvm/Module.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Target/TargetSelect.h"

/* project global headers */
#include "skyeye_dyncom.h"
#include "dyncom/dyncom_llvm.h"
#include "dyncom/tag.h"
#include "translate_all.h"
#include "translate_singlestep.h"
#include "translate_singlestep_bb.h"
#include "function.h"
#include "optimize.h"
#include "stat.h"

#include "memory.h"

#define IS_LITTLE_ENDIAN(cpu) (((cpu)->info.common_flags & CPU_FLAG_ENDIAN_MASK) == CPU_FLAG_ENDIAN_LITTLE)

static inline bool
is_valid_gpr_size(size_t size)
{
	switch (size) {
		case 0: case 1: case 8: case 16: case 32: case 64:
			return true;
		default:
			return false;
	}
}

static inline bool
is_valid_fpr_size(size_t size)
{
	switch (size) {
		case 0: case 32: case 64: case 80: case 128:
			return true;
		default:
			return false;
	}
}

static inline bool
is_valid_vr_size(size_t size)
{
	switch (size) {
		case 0: case 64: case 128:
			return true;
		default:
			return false;
	}
}

//////////////////////////////////////////////////////////////////////
// cpu_t
//////////////////////////////////////////////////////////////////////

cpu_t *
cpu_new(uint32_t flags, uint32_t arch_flags, uint32_t cpu_id)
{
	cpu_t *cpu;

	llvm::InitializeNativeTarget();

	cpu = new cpu_t;
	assert(cpu != NULL);
	memset(&cpu->info, 0, sizeof(cpu->info));
	memset(&cpu->rf, 0, sizeof(cpu->rf));

	cpu->info.name = "noname";
	cpu->info.common_flags = flags;
	cpu->info.arch_flags = arch_flags;
	cpu->id = cpu_id;
#if 0 /* Move the following code to the arch dependent part */
	switch (arch) {
		case CPU_ARCH_XTENSA:
			cpu->f = arch_func_xtensa;
			break;
		default:
			LOG("illegal arch: %d\n", arch);
			exit(1);
	}
#endif
	cpu->dyncom_engine->code_start = 0;
	cpu->dyncom_engine->code_end = 0;
	cpu->dyncom_engine->code_entry = 0;
	cpu->dyncom_engine->tag = NULL;

	uint32_t i;
	for (i = 0; i < 4; i++) {
		cpu->dyncom_engine->tag_array[i] = NULL;
		cpu->dyncom_engine->code_size[i] = 0;
	}

	for (i = 0; i < sizeof(cpu->dyncom_engine->func)/sizeof(*cpu->dyncom_engine->func); i++)
		cpu->dyncom_engine->func[i] = NULL;
	for (i = 0; i < sizeof(cpu->dyncom_engine->fp)/sizeof(*cpu->dyncom_engine->fp); i++)
		cpu->dyncom_engine->fp[i] = NULL;
	cpu->dyncom_engine->functions = 0;

	cpu->dyncom_engine->flags_codegen = CPU_CODEGEN_OPTIMIZE;
	cpu->dyncom_engine->flags_debug = CPU_DEBUG_NONE;
	cpu->dyncom_engine->flags_hint = CPU_HINT_NONE;
	cpu->dyncom_engine->flags = 0;

	// init the frontend
	cpu->f.init(cpu, &cpu->info, &cpu->rf);

	assert(is_valid_gpr_size(cpu->info.register_size[CPU_REG_GPR]) &&
		"the specified GPR size is not guaranteed to work");
	assert(is_valid_fpr_size(cpu->info.register_size[CPU_REG_FPR]) &&
		"the specified FPR size is not guaranteed to work");
	assert(is_valid_vr_size(cpu->info.register_size[CPU_REG_VR]) &&
		"the specified VR size is not guaranteed to work");
	assert(is_valid_gpr_size(cpu->info.register_size[CPU_REG_XR]) &&
		"the specified XR size is not guaranteed to work");

	uint32_t count = cpu->info.register_count[CPU_REG_GPR];
	if (count != 0) {
		cpu->ptr_gpr = (Value **)calloc(count, sizeof(Value *));
		cpu->in_ptr_gpr = (Value **)calloc(count, sizeof(Value *));
	} else {
		cpu->ptr_gpr = NULL;
		cpu->in_ptr_gpr = NULL;
	}

	count = cpu->info.register_count[CPU_REG_XR];
	if (count != 0) {
		cpu->ptr_xr = (Value **)calloc(count, sizeof(Value *));
		cpu->in_ptr_xr = (Value **)calloc(count, sizeof(Value *));
	} else {
		cpu->ptr_xr = NULL;
		cpu->in_ptr_xr = NULL;
	}

	count = cpu->info.register_count[CPU_REG_FPR];
	if (count != 0) {
		cpu->ptr_fpr = (Value **)calloc(count, sizeof(Value *));
		cpu->in_ptr_fpr = (Value **)calloc(count, sizeof(Value *));
	} else {
		cpu->ptr_fpr = NULL;
		cpu->in_ptr_fpr = NULL;
	}

	if (cpu->info.psr_size != 0) {
		cpu->ptr_FLAG = (Value **)calloc(cpu->info.flags_count,
				sizeof(Value*));
		assert(cpu->ptr_FLAG != NULL);
	}

	// init LLVM
	cpu->dyncom_engine->mod = new Module(cpu->info.name, _CTX());
	assert(cpu->dyncom_engine->mod != NULL);
	cpu->dyncom_engine->exec_engine = ExecutionEngine::create(cpu->dyncom_engine->mod);
	assert(cpu->dyncom_engine->exec_engine != NULL);

	// check if FP80 and FP128 are supported by this architecture.
	// XXX there is a better way to do this?
	std::string data_layout = cpu->dyncom_engine->exec_engine->getTargetData()->getStringRepresentation();
	if (data_layout.find("f80") != std::string::npos) {
		LOG("INFO: FP80 supported.\n");
		cpu->dyncom_engine->flags |= CPU_FLAG_FP80;
	}
	if (data_layout.find("f128") != std::string::npos) {
		LOG("INFO: FP128 supported.\n");
		cpu->dyncom_engine->flags |= CPU_FLAG_FP128;
	}

	// check if we need to swap guest memory.
	if (cpu->dyncom_engine->exec_engine->getTargetData()->isLittleEndian()
			^ IS_LITTLE_ENDIAN(cpu))
		cpu->dyncom_engine->flags |= CPU_FLAG_SWAPMEM;

	cpu->timer_total[TIMER_TAG] = 0;
	cpu->timer_total[TIMER_FE] = 0;
	cpu->timer_total[TIMER_BE] = 0;
	cpu->timer_total[TIMER_RUN] = 0;

	return cpu;
}

void
cpu_free(cpu_t *cpu)
{
	if (cpu->f.done != NULL)
		cpu->f.done(cpu);
	if (cpu->dyncom_engine->exec_engine != NULL) {
		if (cpu->dyncom_engine->cur_func != NULL) {
			cpu->dyncom_engine->exec_engine->freeMachineCodeForFunction(cpu->dyncom_engine->cur_func);
			cpu->dyncom_engine->cur_func->eraseFromParent();
		}
		delete cpu->dyncom_engine->exec_engine;
	}
	if (cpu->ptr_FLAG != NULL)
		free(cpu->ptr_FLAG);
	if (cpu->in_ptr_fpr != NULL)
		free(cpu->in_ptr_fpr);
	if (cpu->ptr_fpr != NULL)
		free(cpu->ptr_fpr);
	if (cpu->in_ptr_xr != NULL)
		free(cpu->in_ptr_xr);
	if (cpu->ptr_xr != NULL)
		free(cpu->ptr_xr);
	if (cpu->in_ptr_gpr != NULL)
		free(cpu->in_ptr_gpr);
	if (cpu->ptr_gpr != NULL)
		free(cpu->ptr_gpr);

	delete cpu;
}

void
cpu_set_ram(cpu_t*cpu, uint8_t *r)
{
	cpu->dyncom_engine->RAM = r;
}

void
cpu_set_flags_codegen(cpu_t *cpu, uint32_t f)
{
	cpu->dyncom_engine->flags_codegen = f;
}

void
cpu_set_flags_debug(cpu_t *cpu, uint32_t f)
{
	cpu->dyncom_engine->flags_debug = f;
}

void
cpu_set_flags_hint(cpu_t *cpu, uint32_t f)
{
	cpu->dyncom_engine->flags_hint = f;
}

void
cpu_tag(cpu_t *cpu, addr_t pc)
{
	update_timing(cpu, TIMER_TAG, true);
	tag_start(cpu, pc);
	update_timing(cpu, TIMER_TAG, false);
}

void save_addr_in_func(cpu_t *cpu, void *native_code_func)
{
	bbaddr_map &bb_addr = cpu->dyncom_engine->func_bb[cpu->dyncom_engine->cur_func];
	bbaddr_map::iterator i = bb_addr.begin();
	for (; i != bb_addr.end(); i++)
		cpu->dyncom_engine->fmap[i->first] = native_code_func;
}

static void
cpu_translate_function(cpu_t *cpu)
{
	BasicBlock *bb_ret, *bb_trap, *label_entry, *bb_start;

	addr_t start_addr = cpu->f.get_pc(cpu, cpu->rf.grf);

	/* create function and fill it with std basic blocks */
	cpu->dyncom_engine->cur_func = cpu_create_function(cpu, "jitmain", &bb_ret, &bb_trap, &label_entry);

	/* TRANSLATE! */
	update_timing(cpu, TIMER_FE, true);
	if (cpu->dyncom_engine->flags_debug & CPU_DEBUG_SINGLESTEP) {
		bb_start = cpu_translate_singlestep(cpu, bb_ret, bb_trap);
	} else if (cpu->dyncom_engine->flags_debug & CPU_DEBUG_SINGLESTEP_BB) {
		bb_start = cpu_translate_singlestep_bb(cpu, bb_ret, bb_trap);
	} else {
		bb_start = cpu_translate_all(cpu, bb_ret, bb_trap);
	}
	update_timing(cpu, TIMER_FE, false);

	/* finish entry basicblock */
	BranchInst::Create(bb_start, label_entry);

	/* make sure everything is OK */
	verifyFunction(*cpu->dyncom_engine->cur_func, AbortProcessAction);

	if (cpu->dyncom_engine->flags_debug & CPU_DEBUG_PRINT_IR)
		cpu->dyncom_engine->mod->dump();

	if (cpu->dyncom_engine->flags_codegen & CPU_CODEGEN_OPTIMIZE) {
		LOG("*** Optimizing...");
		optimize(cpu);
		LOG("done.\n");
		if (cpu->dyncom_engine->flags_debug & CPU_DEBUG_PRINT_IR_OPTIMIZED)
			cpu->dyncom_engine->mod->dump();
	}

	LOG("*** Translating...");
	update_timing(cpu, TIMER_BE, true);
	cpu->dyncom_engine->fp[cpu->dyncom_engine->functions] = cpu->dyncom_engine->exec_engine->getPointerToFunction(cpu->dyncom_engine->cur_func);
	//cpu->dyncom_engine->fmap[start_addr] = cpu->dyncom_engine->fp[cpu->dyncom_engine->functions];
	save_addr_in_func(cpu, cpu->dyncom_engine->fp[cpu->dyncom_engine->functions]);
	LOG("Generate native code for %x\n", start_addr);
	update_timing(cpu, TIMER_BE, false);
	LOG("done.\n");

	cpu->dyncom_engine->functions++;/* Bug."functions" member could not be reset. */
}

/* forces ahead of time translation (e.g. for benchmarking the run) */
void
cpu_translate(cpu_t *cpu)
{
	/* on demand translation */
	if (cpu->dyncom_engine->tags_dirty)
		cpu_translate_function(cpu);

	cpu->dyncom_engine->tags_dirty = false;
}

typedef int (*fp_t)(uint8_t *RAM, void *grf, void *frf, debug_function_t fp, read_memory_t readfp, write_memory_t writefp);

#ifdef __GNUC__
void __attribute__((noinline))
breakpoint() {
asm("nop");
}
#else
void breakpoint() {}
#endif

int
cpu_run(cpu_t *cpu, debug_function_t debug_function)
{
	addr_t pc = 0, orig_pc = 0;
	uint64_t icounter, orig_icounter;
	uint32_t i;
	int ret;
	bool success;
	bool do_translate = true;
	fp_t pfunc = NULL;

	/* try to find the entry in all functions */
	while(true) {
		pc = cpu->f.get_pc(cpu, cpu->rf.grf);
		fast_map &func_addr = cpu->dyncom_engine->fmap;
		fast_map::const_iterator it = func_addr.find(pc);
		if (it != func_addr.end()) {
			pfunc = (fp_t)it->second;
			do_translate = false;
		} else
			return JIT_RETURN_FUNCNOTFOUND;

		if (do_translate) {
			cpu_translate(cpu);
			pc = cpu->f.get_pc(cpu, cpu->rf.grf);
		}

		//orig_pc = pc;
		//orig_icounter = REG(SR(ICOUNTER));
		success = false;
		update_timing(cpu, TIMER_RUN, true);
		breakpoint();
		#if PRINT_REG
		for (int i = 0; i < 16; i++) {
			LOG("%d:%x ", i, *(uint32_t*)((uint8_t*)cpu->rf.grf + 4*i));
		}
		LOG("\n");
		LOG("############### Begin to execute JIT\n");
		#endif
		//ret = FP(cpu->dyncom_engine->RAM, cpu->rf.grf, cpu->rf.frf, debug_function, WindowCheck, xtensa_read_memory, xtensa_write_memory);
		ret = pfunc(cpu->dyncom_engine->RAM, cpu->rf.grf, cpu->rf.frf, debug_function, read_memory, write_memory);
		//*(uint32_t*)((uint8_t*)cpu->rf.grf + 8) = 0;
		//ret = FP(cpu->dyncom_engine->RAM, cpu->rf.grf, cpu->rf.frf, debug_function);
		#if PRINT_REG
		for (int i = 0; i < 16; i++) {
			LOG("%d:%x ", i, *(uint32_t*)((uint8_t*)cpu->rf.grf + 4*i));
		}
		LOG("pc : %x\n ret : %x", cpu->f.get_pc(cpu, cpu->rf.grf), ret);
		LOG("\n");
		#endif
		update_timing(cpu, TIMER_RUN, false);
		//pc = cpu->f.get_pc(cpu, cpu->rf.grf);
		//icounter = REG(SR(ICOUNTER));
		//pc = 0x4d495354;
		//return ret;
		if (ret != JIT_RETURN_FUNCNOTFOUND)
			return ret;
		if (!is_inside_code_area(cpu, pc))
			return ret;
		/* simulator run new instructions ? */
		if (icounter != orig_icounter) {
			success = true;
			//break;
		}
		//}
		#if 1
		if (!success) {
			LOG("{%llx}", pc);
			cpu_tag(cpu, pc);
			do_translate = true;
		}
		#endif
	}
}
//LOG("%d\n", __LINE__);

void
cpu_flush(cpu_t *cpu)
{
	cpu->dyncom_engine->exec_engine->freeMachineCodeForFunction(cpu->dyncom_engine->cur_func);
	cpu->dyncom_engine->cur_func->eraseFromParent();

	cpu->dyncom_engine->functions = 0;

	// reset bb caching mapping
	cpu->dyncom_engine->func_bb.clear();

//	delete cpu->dyncom_engine->mod;
//	cpu->dyncom_engine->mod = NULL;
}

void
cpu_print_statistics(cpu_t *cpu)
{
	//printf("icounter = %8lld\n", REG(SR(ICOUNTER)));
	printf("tag = %8lld\n", cpu->timer_total[TIMER_TAG]);
	printf("fe  = %8lld\n", cpu->timer_total[TIMER_FE]);
	printf("be  = %8lld\n", cpu->timer_total[TIMER_BE]);
	printf("run = %8lld\n", cpu->timer_total[TIMER_RUN]);
}
//LOG("%s:%d\n", __func__, __LINE__);