/*
    vfp/vfpinstr.c - ARM VFPv3 emulation unit - Individual instructions data
    Copyright (C) 2003 Skyeye Develop Group
    for help please send mail to <skyeye-developer@lists.gro.clinux.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* Notice: this file should not be compiled as is, and is meant to be
   included in other files only. */

/* ----------------------------------------------------------------------- */
/* CDP instructions */
/* cond 1110 opc1 CRn- CRd- copr op20 CRm- CDP */

/* ----------------------------------------------------------------------- */
/* VMLA */
/* cond 1110 0D00 Vn-- Vd-- 101X N0M0 Vm-- */
#define vfpinstr 	vmla
#define vfpinstr_inst 	vmla_inst
#define VFPLABEL_INST 	VMLA_INST
#ifdef VFP_DECODE
{"vmla",        5,      ARMVFP2,        23, 27, 0x1c,   20, 21, 0x0,    9, 11, 0x5,     6, 6, 0,        4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vmla",        0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vmla_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VMLA :\n");
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 0 && (OPC_2 & 0x2) == 0)
{
	DBG("VMLA :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);

	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VMLS */
/* cond 1110 0D00 Vn-- Vd-- 101X N1M0 Vm-- */
#define vfpinstr 	vmls
#define vfpinstr_inst 	vmls_inst
#define VFPLABEL_INST 	VMLS_INST
#ifdef VFP_DECODE
{"vmls",        5,      ARMVFP2,        23, 27, 0x1c,   20, 21, 0x0,    9, 11, 0x5,     6, 6, 1,        4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vmls",        0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vmls_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VMLS :\n");
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 0 && (OPC_2 & 0x2) == 2)
{
	DBG("VMLS :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VNMLA */
/* cond 1110 0D01 Vn-- Vd-- 101X N1M0 Vm-- */
#define vfpinstr 	vnmla
#define vfpinstr_inst 	vnmla_inst
#define VFPLABEL_INST 	VNMLA_INST
#ifdef VFP_DECODE
{"vnmla",       5,      ARMVFP2,        23, 27, 0x1c,   20, 21, 0x0,    9, 11, 0x5,     6, 6, 1,        4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vnmla",       0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vnmla_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VNMLA :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 1 && (OPC_2 & 0x2) == 2)
{
	DBG("VNMLA :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VNMLS */
/* cond 1110 0D01 Vn-- Vd-- 101X N0M0 Vm-- */
#define vfpinstr 	vnmls
#define vfpinstr_inst 	vnmls_inst
#define VFPLABEL_INST 	VNMLS_INST
#ifdef VFP_DECODE
{"vnmls",       5,      ARMVFP2,        23, 27, 0x1c,   20, 21, 0x0,    9, 11, 0x5,     6, 6, 0,        4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vnmls",       0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vnmls_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VNMLS :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 1 && (OPC_2 & 0x2) == 0)
{
	DBG("VNMLS :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VNMUL */
/* cond 1110 0D10 Vn-- Vd-- 101X N0M0 Vm-- */
#define vfpinstr 	vnmul
#define vfpinstr_inst 	vnmul_inst
#define VFPLABEL_INST 	VNMUL_INST
#ifdef VFP_DECODE
{"vnmul",       5,      ARMVFP2,        23, 27, 0x1c,   20, 21, 0x2,    9, 11, 0x5,     6, 6, 1,        4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vnmul",       0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vnmul_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VNMUL :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 2 && (OPC_2 & 0x2) == 2)
{
	DBG("VNMUL :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VMUL */
/* cond 1110 0D10 Vn-- Vd-- 101X N0M0 Vm-- */
#define vfpinstr 	vmul
#define vfpinstr_inst 	vmul_inst
#define VFPLABEL_INST 	VMUL_INST
#ifdef VFP_DECODE
{"vmul",        5,      ARMVFP2,        23, 27, 0x1c,  20, 21, 0x2,     9, 11, 0x5,      6, 6, 0,     4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vmul",        0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vmul_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VMUL :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 2 && (OPC_2 & 0x2) == 0)
{
	DBG("VMUL :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VADD */
/* cond 1110 0D11 Vn-- Vd-- 101X N0M0 Vm-- */
#define vfpinstr 	vadd
#define vfpinstr_inst 	vadd_inst
#define VFPLABEL_INST 	VADD_INST
#ifdef VFP_DECODE
{"vadd",        5,      ARMVFP2,        23, 27, 0x1c,  20, 21, 0x3,     9, 11, 0x5,      6, 6, 0,     4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vadd",        0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vadd_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VADD :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 3 && (OPC_2 & 0x2) == 0)
{
	DBG("VADD :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VSUB */
/* cond 1110 0D11 Vn-- Vd-- 101X N1M0 Vm-- */
#define vfpinstr 	vsub
#define vfpinstr_inst 	vsub_inst
#define VFPLABEL_INST 	VSUB_INST
#ifdef VFP_DECODE
{"vsub",        5,      ARMVFP2,        23, 27, 0x1c,  20, 21, 0x3,     9, 11, 0x5,      6, 6, 1,     4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vsub",        0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vsub_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VSUB :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 3 && (OPC_2 & 0x2) == 2)
{
	DBG("VSUB :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VDIV */
/* cond 1110 1D00 Vn-- Vd-- 101X N0M0 Vm-- */
#define vfpinstr 	vdiv
#define vfpinstr_inst 	vdiv_inst
#define VFPLABEL_INST 	VDIV_INST
#ifdef VFP_DECODE
{"vdiv",        5,      ARMVFP2,        23, 27, 0x1d,  20, 21, 0x0,     9, 11, 0x5,      6, 6, 0,     4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vdiv",        0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vdiv_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VDIV :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 0xA && (OPC_2 & 0x2) == 0)
{
	DBG("VDIV :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VMOVI move immediate */
/* cond 1110 1D11 im4H Vd-- 101X 0000 im4L */
/* cond 1110 opc1 CRn- CRd- copr op20 CRm- CDP */
#define vfpinstr 	vmovi
#define vfpinstr_inst 	vmovi_inst
#define VFPLABEL_INST 	VMOVI_INST
#ifdef VFP_DECODE
{"vmov(i)",       4,      ARMVFP3,        23, 27, 0x1d,   20, 21, 0x3,    9, 11, 0x5,     4, 7, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vmov(i)",       0,      ARMVFP3, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vmovi_inst {
	unsigned int single;
	unsigned int d;
	unsigned int imm;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;
	
	inst_cream->single   = BIT(inst, 8) == 0;
	inst_cream->d        = (inst_cream->single ? BITS(inst,12,15)<<1 | BIT(inst,22) : BITS(inst,12,15) | BIT(inst,22)<<4);
	unsigned int imm8 = BITS(inst, 16, 19) << 4 | BITS(inst, 0, 3);
	if (inst_cream->single)
		inst_cream->imm = BIT(imm8, 7)<<31 | (BIT(imm8, 6)==0)<<30 | (BIT(imm8, 6) ? 0x1f : 0)<<25 | BITS(imm8, 0, 5)<<19;
	else
		inst_cream->imm = BIT(imm8, 7)<<31 | (BIT(imm8, 6)==0)<<30 | (BIT(imm8, 6) ? 0xff : 0)<<22 | BITS(imm8, 0, 5)<<16;
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		VMOVI(cpu, inst_cream->single, inst_cream->d, inst_cream->imm);
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ( (OPC_1 & 0xb) == 0xb && BITS(4, 7) == 0)
{
	unsigned int single   = BIT(8) == 0;
	unsigned int d        = (single ? BITS(12,15)<<1 | BIT(22) : BITS(12,15) | BIT(22)<<4);
	unsigned int imm;
	instr = BITS(16, 19) << 4 | BITS(0, 3); /* FIXME dirty workaround to get a correct imm */
	if (single) {
		imm = BIT(7)<<31 | (BIT(6)==0)<<30 | (BIT(6) ? 0x1f : 0)<<25 | BITS(0, 5)<<19;
	} else {
		imm = BIT(7)<<31 | (BIT(6)==0)<<30 | (BIT(6) ? 0xff : 0)<<22 | BITS(0, 5)<<16;
	}
	VMOVI(state, single, d, imm);
	return ARMul_DONE;
}
#endif
#ifdef VFP_CDP_IMPL
void VMOVI(ARMul_State * state, ARMword single, ARMword d, ARMword imm)
{
	DBG("VMOV(I) :\n");
		
	if (single)
	{
		DBG("\ts%d <= [%x]\n", d, imm);
		state->ExtReg[d] = imm;
	}
	else
	{
		/* Check endian please */
		DBG("\ts[%d-%d] <= [%x-%x]\n", d*2+1, d*2, imm, 0);
		state->ExtReg[d*2+1] = imm;
		state->ExtReg[d*2] = 0;
	}
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VMOVR move register */
/* cond 1110 1D11 0000 Vd-- 101X 01M0 Vm-- */
/* cond 1110 opc1 CRn- CRd- copr op20 CRm- CDP */
#define vfpinstr 	vmovr
#define vfpinstr_inst 	vmovr_inst
#define VFPLABEL_INST 	VMOVR_INST
#ifdef VFP_DECODE
{"vmov(r)",       5,      ARMVFP3,        23, 27, 0x1d,   16, 21, 0x30,    9, 11, 0x5,    6, 7, 1,        4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vmov(r)",       0,      ARMVFP3, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vmovr_inst {
	unsigned int single;
	unsigned int d;
	unsigned int m;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	VFP_DEBUG_UNTESTED(VMOVR);
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;
	
	inst_cream->single   = BIT(inst, 8) == 0;
	inst_cream->d        = (inst_cream->single ? BITS(inst,12,15)<<1 | BIT(inst,22) : BITS(inst,12,15) | BIT(inst,22)<<4);
	inst_cream->m        = (inst_cream->single ? BITS(inst, 0, 3)<<1 | BIT(inst, 5) : BITS(inst, 0, 3) | BIT(inst, 5)<<4);
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		VMOVR(cpu, inst_cream->single, inst_cream->d, inst_cream->m);
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ( (OPC_1 & 0xb) == 0xb && CRn == 0 && (OPC_2 & 0x6) == 0x2 )
{
	unsigned int single   = BIT(8) == 0;
	unsigned int d        = (single ? BITS(12,15)<<1 | BIT(22) : BITS(12,15) | BIT(22)<<4);
	unsigned int m        = (single ? BITS( 0, 3)<<1 | BIT( 5) : BITS( 0, 3) | BIT( 5)<<4);;
	VMOVR(state, single, d, m);
	return ARMul_DONE;
}
#endif
#ifdef VFP_CDP_IMPL
void VMOVR(ARMul_State * state, ARMword single, ARMword d, ARMword m)
{
	DBG("VMOV(R) :\n");
		
	if (single)
	{
		DBG("\ts%d <= s%d[%x]\n", d, m, state->ExtReg[m]);
		state->ExtReg[d] = state->ExtReg[m];
	}
	else
	{
		/* Check endian please */
		DBG("\ts[%d-%d] <= s[%d-%d][%x-%x]\n", d*2+1, d*2, m*2+1, m*2, state->ExtReg[m*2+1], state->ExtReg[m*2]);
		state->ExtReg[d*2+1] = state->ExtReg[m*2+1];
		state->ExtReg[d*2] = state->ExtReg[m*2];
	}
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VABS */
/* cond 1110 1D11 0000 Vd-- 101X 11M0 Vm-- */
#define vfpinstr 	vabs
#define vfpinstr_inst 	vabs_inst
#define VFPLABEL_INST 	VABS_INST
#ifdef VFP_DECODE
{"vabs",        5,      ARMVFP2,        23, 27, 0x1d,  16, 21, 0x30,    9, 11, 0x5,      6, 7, 3,     4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vabs",        0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vabs_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;VFP_DEBUG_UNTESTED(VABS);
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VABS :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 0xB && CRn == 0 && (OPC_2 & 0x7) == 6)
{
	DBG("VABS :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VNEG */
/* cond 1110 1D11 0001 Vd-- 101X 11M0 Vm-- */
#define vfpinstr 	vneg
#define vfpinstr_inst 	vneg_inst
#define VFPLABEL_INST 	VNEG_INST
#ifdef VFP_DECODE
{"vneg",        5,      ARMVFP2,        23, 27, 0x1d,  16, 21, 0x30,    9, 11, 0x5,      6, 7, 1,     4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vneg",        0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vneg_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;VFP_DEBUG_UNTESTED(VNEG);
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;

		DBG("VNEG :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 0xB && CRn == 1 && (OPC_2 & 0x7) == 2)
{
	DBG("VNEG :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VSQRT */
/* cond 1110 1D11 0001 Vd-- 101X 11M0 Vm-- */
#define vfpinstr 	vsqrt
#define vfpinstr_inst 	vsqrt_inst
#define VFPLABEL_INST 	VSQRT_INST
#ifdef VFP_DECODE
{"vsqrt",        5,      ARMVFP2,        23, 27, 0x1d,  16, 21, 0x31,    9, 11, 0x5,      6, 7, 3,     4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vsqrt",        0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vsqrt_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VSQRT :\n");
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 0xB && CRn == 1 && (OPC_2 & 0x7) == 6)
{
	DBG("VSQRT :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VCMP VCMPE */
/* cond 1110 1D11 0100 Vd-- 101X E1M0 Vm-- Encoding 1 */
#define vfpinstr 	vcmp
#define vfpinstr_inst 	vcmp_inst
#define VFPLABEL_INST 	VCMP_INST
#ifdef VFP_DECODE
{"vcmp",        5,      ARMVFP2,        23, 27, 0x1d,  16, 21, 0x34,    9, 11, 0x5,      6, 6, 1,     4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vcmp",        0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vcmp_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;

		DBG("VCMP(1) :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 0xB && CRn == 4 && (OPC_2 & 0x2) == 2)
{
	DBG("VCMP(1) :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VCMP VCMPE */
/* cond 1110 1D11 0100 Vd-- 101X E1M0 Vm-- Encoding 2 */
#define vfpinstr 	vcmp2
#define vfpinstr_inst 	vcmp2_inst
#define VFPLABEL_INST 	VCMP2_INST
#ifdef VFP_DECODE
{"vcmp2",        5,      ARMVFP2,        23, 27, 0x1d,  16, 21, 0x35,    9, 11, 0x5,     0, 6, 0x40},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vcmp2",        0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vcmp2_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VCMP(2) :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 0xB && CRn == 5 && (OPC_2 & 0x2) == 2 && CRm == 0)
{
	DBG("VCMP(2) :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VCVTBDS between double and single */
/* cond 1110 1D11 0111 Vd-- 101X 11M0 Vm-- */
#define vfpinstr 	vcvtbds
#define vfpinstr_inst 	vcvtbds_inst
#define VFPLABEL_INST 	VCVTBDS_INST
#ifdef VFP_DECODE
{"vcvt(bds)",   5,      ARMVFP2,        23, 27, 0x1d,  16, 21, 0x37,    9, 11, 0x5,      6, 7, 3,     4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vcvt(bds)",        0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vcvtbds_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VCVT(BDS) :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 0xB && CRn == 7 && (OPC_2 & 0x6) == 6)
{
	DBG("VCVT(BDS) :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VCVTBFF between floating point and fixed point */
/* cond 1110 1D11 1op2 Vd-- 101X X1M0 Vm-- */
#define vfpinstr 	vcvtbff
#define vfpinstr_inst 	vcvtbff_inst
#define VFPLABEL_INST 	VCVTBFF_INST
#ifdef VFP_DECODE
{"vcvt(bff)",   6,      ARMVFP3,        23, 27, 0x1d,  19, 21, 0x7,     17, 17, 0x1,      9, 11, 0x5,  	6, 6, 1},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vcvt(bff)",   0,      ARMVFP3,         4, 4, 1},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vcvtbff_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;VFP_DEBUG_UNTESTED(VCVTBFF);
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VCVT(BFF) :\n");

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 0xB && CRn >= 0xA && (OPC_2 & 0x2) == 2)
{
	DBG("VCVT(BFF) :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VCVTBFI between floating point and integer */
/* cond 1110 1D11 1op2 Vd-- 101X X1M0 Vm-- */
#define vfpinstr 	vcvtbfi
#define vfpinstr_inst 	vcvtbfi_inst
#define VFPLABEL_INST 	VCVTBFI_INST
#ifdef VFP_DECODE
{"vcvt(bfi)",   5,      ARMVFP2,        23, 27, 0x1d,  19, 21, 0x7,     9, 11, 0x5,      6, 6, 1,     4, 4, 0},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vcvt(bfi)",   0,      ARMVFP2, 0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vcvtbfi_inst {
	unsigned int instr;
	unsigned int dp_operation;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->dp_operation = BIT(inst, 8);
	inst_cream->instr = inst;

	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		DBG("VCVT(BFI) :\n");
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		int ret;
		
		if (inst_cream->dp_operation)
			ret = vfp_double_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);
		else
			ret = vfp_single_cpdo(inst_cream->instr, cpu->VFP[VFP_FPSCR]);

		CHECK_VFP_CDP_RET;
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_CDP_TRANS
if ((OPC_1 & 0xB) == 0xB && CRn > 7 && (OPC_2 & 0x2) == 2)
{
	DBG("VCVT(BFI) :\n");
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* MRC / MCR instructions */
/* cond 1110 AAAL XXXX XXXX 101C XBB1 XXXX */
/* cond 1110 op11 CRn- Rt-- copr op21 CRm- */

/* ----------------------------------------------------------------------- */
/* VMOVBRS between register and single precision */
/* cond 1110 000o Vn-- Rt-- 1010 N001 0000 */
/* cond 1110 op11 CRn- Rt-- copr op21 CRm- MRC */
#define vfpinstr 	vmovbrs
#define vfpinstr_inst 	vmovbrs_inst
#define VFPLABEL_INST 	VMOVBRS_INST
#ifdef VFP_DECODE
{"vmovbrs",    3,    ARMVFP2,    21, 27, 0x70,    8, 11, 0xA,    0, 6, 0x10},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vmovbrs",    0,    ARMVFP2,    0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vmovbrs_inst {
	unsigned int to_arm;
	unsigned int t;
	unsigned int n;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx     = index;
	inst_base->br     = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->to_arm   = BIT(inst, 20) == 1;
	inst_cream->t        = BITS(inst, 12, 15);
	inst_cream->n        = BIT(inst, 7) | BITS(inst, 16, 19)<<1;

	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
           
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		VMOVBRS(cpu, inst_cream->to_arm, inst_cream->t, inst_cream->n, &(cpu->Reg[inst_cream->t]));
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_MRC_TRANS
if (OPC_1 == 0x0 && CRm == 0 && (OPC_2 & 0x3) == 0)
{
	/* VMOV r to s */
	/* Transfering Rt is not mandatory, as the value of interest is pointed by value */
	VMOVBRS(state, BIT(20), Rt, BIT(7)|CRn<<1, value);
	return ARMul_DONE;
}
#endif
#ifdef VFP_MCR_TRANS
if (OPC_1 == 0x0 && CRm == 0 && (OPC_2 & 0x3) == 0)
{
	/* VMOV s to r */
	/* Transfering Rt is not mandatory, as the value of interest is pointed by value */
	VMOVBRS(state, BIT(20), Rt, BIT(7)|CRn<<1, &value);
	return ARMul_DONE;
}
#endif
#ifdef VFP_MRC_IMPL
void VMOVBRS(ARMul_State * state, ARMword to_arm, ARMword t, ARMword n, ARMword *value)
{
	DBG("VMOV(BRS) :\n");
	if (to_arm)
	{
		DBG("\tr%d <= s%d=[%x]\n", t, n, state->ExtReg[n]);
		*value = state->ExtReg[n];
	}
	else
	{
		DBG("\ts%d <= r%d=[%x]\n", n, t, *value);
		state->ExtReg[n] = *value;
	}
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VMSR */
/* cond 1110 1110 reg- Rt-- 1010 0001 0000 */
/* cond 1110 op10 CRn- Rt-- copr op21 CRm- MCR */
#define vfpinstr 	vmsr
#define vfpinstr_inst 	vmsr_inst
#define VFPLABEL_INST 	VMSR_INST
#ifdef VFP_DECODE
{"vmsr",    2,    ARMVFP2,    20, 27, 0xEE,    0, 11, 0xA10},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vmsr",    0,    ARMVFP2,    0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vmsr_inst {
	unsigned int reg;
	unsigned int Rd;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx     = index;
	inst_base->br     = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->reg  = BITS(inst, 16, 19);
	inst_cream->Rd   = BITS(inst, 12, 15);
   
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		/* FIXME: special case for access to FPSID and FPEXC, VFP must be disabled ,
		   and in privilegied mode */
		/* Exceptions must be checked, according to v7 ref manual */
		CHECK_VFP_ENABLED;
           
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		VMSR(cpu, inst_cream->reg, inst_cream->Rd);
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_MCR_TRANS
if (OPC_1 == 0x7 && CRm == 0 && OPC_2 == 0)
{
	VMSR(state, CRn, Rt);
	return ARMul_DONE;
}
#endif
#ifdef VFP_MCR_IMPL
void VMSR(ARMul_State * state, ARMword reg, ARMword Rt)
{
	if (reg == 1)
	{
		DBG("VMSR :\tfpscr <= r%d=[%x]\n", Rt, state->Reg[Rt]);
		state->VFP[VFP_FPSCR] = state->Reg[Rt];
	}
	else if (reg == 8)
	{
		DBG("VMSR :\tfpexc <= r%d=[%x]\n", Rt, state->Reg[Rt]);
		state->VFP[VFP_FPEXC] = state->Reg[Rt];
	}
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	//DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	//arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	arm_tag_continue(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	//DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	//arch_arm_undef(cpu, bb, instr);
	DBG("VMSR :");
	if(RD == 15) {
		printf("in %s is not implementation.\n", __FUNCTION__);
		exit(-1);
	}
	
	Value *data = NULL;
	int reg = RN;
	int Rt   = RD;
	if (reg == 1)
	{
		LET(VFP_FPSCR, R(Rt));
		DBG("\tflags <= fpscr\n");
	}
	else
	{
		switch (reg)
		{
		case 8:
			LET(VFP_FPEXC, R(Rt));
			DBG("\tfpexc <= r%d \n", Rt);
			break;
		default:
			DBG("\tSUBARCHITECTURE DEFINED\n");
			break;
		}
	}
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VMOVBRC register to scalar */
/* cond 1110 0XX0 Vd-- Rt-- 1011 DXX1 0000 */
/* cond 1110 op10 CRn- Rt-- copr op21 CRm- MCR */
#define vfpinstr 	vmovbrc
#define vfpinstr_inst 	vmovbrc_inst
#define VFPLABEL_INST 	VMOVBRC_INST
#ifdef VFP_DECODE
{"vmovbrc",    4,    ARMVFP2,    23, 27, 0x1C,    20, 20, 0x0,    8,11,0xB,    0,4,0x10},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vmovbrc",    0,    ARMVFP2,    0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vmovbrc_inst {
	unsigned int esize;
	unsigned int index;
	unsigned int d;
	unsigned int t;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx     = index;
	inst_base->br     = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->d     = BITS(inst, 16, 19)|BIT(inst, 7)<<4;
	inst_cream->t     = BITS(inst, 12, 15);
	/* VFP variant of instruction */
	inst_cream->esize = 32;
	inst_cream->index = BIT(inst, 21);
   
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;
		
		VFP_DEBUG_UNIMPLEMENTED(VMOVBRC);
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_MCR_TRANS
if ((OPC_1 & 0x4) == 0 && CoProc == 11 && CRm == 0)
{
	VFP_DEBUG_UNIMPLEMENTED(VMOVBRC);
	return ARMul_DONE;
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VMRS */
/* cond 1110 1111 CRn- Rt-- 1010 0001 0000 */
/* cond 1110 op11 CRn- Rt-- copr op21 CRm- MRC */
#define vfpinstr 	vmrs
#define vfpinstr_inst 	vmrs_inst
#define VFPLABEL_INST 	VMRS_INST
#ifdef VFP_DECODE
{"vmrs",        2,      ARMVFP2,        20, 27, 0xEF,     0, 11, 0xa10},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vmrs",    0,    ARMVFP2,    0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vmrs_inst {
	unsigned int reg;
	unsigned int Rt;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx     = index;
	inst_base->br     = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->reg  = BITS(inst, 16, 19);
	inst_cream->Rt	 = BITS(inst, 12, 15);
   
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		/* FIXME: special case for access to FPSID and FPEXC, VFP must be disabled,
		   and in privilegied mode */
		/* Exceptions must be checked, according to v7 ref manual */
		CHECK_VFP_ENABLED;
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;
		
		DBG("VMRS :");
	
		if (inst_cream->reg == 1) /* FPSCR */
		{
			if (inst_cream->Rt != 15)
			{	
				cpu->Reg[inst_cream->Rt] = cpu->VFP[VFP_FPSCR];
				DBG("\tr%d <= fpscr[%08x]\n", inst_cream->Rt, cpu->VFP[VFP_FPSCR]);
			}
			else
			{	
				cpu->NFlag = (cpu->VFP[VFP_FPSCR] >> 31) & 1;
				cpu->ZFlag = (cpu->VFP[VFP_FPSCR] >> 30) & 1;
				cpu->CFlag = (cpu->VFP[VFP_FPSCR] >> 29) & 1;
				cpu->VFlag = (cpu->VFP[VFP_FPSCR] >> 28) & 1;
				DBG("\tflags <= fpscr[%1xxxxxxxx]\n", cpu->VFP[VFP_FPSCR]>>28);
			}
		} 
		else
		{
			switch (inst_cream->reg)
			{
			case 0:
				cpu->Reg[inst_cream->Rt] = cpu->VFP[VFP_FPSID];
				DBG("\tr%d <= fpsid[%08x]\n", inst_cream->Rt, cpu->VFP[VFP_FPSID]);
				break;
			case 6:
				/* MVFR1, VFPv3 only ? */
				DBG("\tr%d <= MVFR1 unimplemented\n", inst_cream->Rt);
				break;
			case 7:
				/* MVFR0, VFPv3 only? */
				DBG("\tr%d <= MVFR0 unimplemented\n", inst_cream->Rt);
				break;
			case 8:
				cpu->Reg[inst_cream->Rt] = cpu->VFP[VFP_FPEXC];
				DBG("\tr%d <= fpexc[%08x]\n", inst_cream->Rt, cpu->VFP[VFP_FPEXC]);
				break;
			default:
				DBG("\tSUBARCHITECTURE DEFINED\n");
				break;
			}
		}
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_MRC_TRANS
if (OPC_1 == 0x7 && CRm == 0 && OPC_2 == 0)
{
	VMRS(state, CRn, Rt, value);
	return ARMul_DONE;
}
#endif
#ifdef VFP_MRC_IMPL
void VMRS(ARMul_State * state, ARMword reg, ARMword Rt, ARMword * value)
{
	DBG("VMRS :");
	if (reg == 1)
	{
		if (Rt != 15)
		{
			*value = state->VFP[VFP_FPSCR];
			DBG("\tr%d <= fpscr[%08x]\n", Rt, state->VFP[VFP_FPSCR]);
		}
		else
		{
			*value = state->VFP[VFP_FPSCR] ;
			DBG("\tflags <= fpscr[%1xxxxxxxx]\n", state->VFP[VFP_FPSCR]>>28);
		}
	}
	else
	{
		switch (reg)
		{
		case 0:
			*value = state->VFP[VFP_FPSID];
			DBG("\tr%d <= fpsid[%08x]\n", Rt, state->VFP[VFP_FPSID]);
			break;
		case 6:
			/* MVFR1, VFPv3 only ? */
			DBG("\tr%d <= MVFR1 unimplemented\n", Rt);
			break;
		case 7:
			/* MVFR0, VFPv3 only? */
			DBG("\tr%d <= MVFR0 unimplemented\n", Rt);
			break;
		case 8:
			*value = state->VFP[VFP_FPEXC];
			DBG("\tr%d <= fpexc[%08x]\n", Rt, state->VFP[VFP_FPEXC]);
			break;
		default:
			DBG("\tSUBARCHITECTURE DEFINED\n");
			break;
		}
	}
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	//DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	//arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	arm_tag_continue(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	//DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	//arch_arm_undef(cpu, bb, instr);
	DBG("VMRS :");
	if(RD == 15) {
		printf("in %s is not implementation.\n", __FUNCTION__);
		exit(-1);
	}
	
	Value *data = NULL;
	int reg = RN;
	int Rt   = RD;
	if (reg == 1)
	{
		if (Rt != 15)
		{
			LET(Rt, R(VFP_FPSCR));
			DBG("\tr%d <= fpscr\n", Rt);
		}
		else
		{
			LET(Rt, R(VFP_FPSCR));
			DBG("\tflags <= fpscr\n");
		}
	}
	else
	{
		switch (reg)
		{
		case 0:
			LET(Rt, R(VFP_FPSID));
			DBG("\tr%d <= fpsid\n", Rt);
			break;
		case 6:
			/* MVFR1, VFPv3 only ? */
			DBG("\tr%d <= MVFR1 unimplemented\n", Rt);
			break;
		case 7:
			/* MVFR0, VFPv3 only? */
			DBG("\tr%d <= MVFR0 unimplemented\n", Rt);
			break;
		case 8:
			LET(Rt, R(VFP_FPEXC));
			DBG("\tr%d <= fpexc\n", Rt);
			break;
		default:
			DBG("\tSUBARCHITECTURE DEFINED\n");
			break;
		}
	}

	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VMOVBCR scalar to register */
/* cond 1110 XXX1 Vd-- Rt-- 1011 NXX1 0000 */
/* cond 1110 op11 CRn- Rt-- copr op21 CRm- MCR */
#define vfpinstr 	vmovbcr
#define vfpinstr_inst 	vmovbcr_inst
#define VFPLABEL_INST 	VMOVBCR_INST
#ifdef VFP_DECODE
{"vmovbcr",    4,    ARMVFP2,    24, 27, 0xE,    20, 20, 1,    8, 11,0xB,    0,4, 0x10},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vmovbcr",    0,    ARMVFP2,    0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vmovbcr_inst {
	unsigned int esize;
	unsigned int index;
	unsigned int d;
	unsigned int t;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx     = index;
	inst_base->br     = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->d     = BITS(inst, 16, 19)|BIT(inst, 7)<<4;
	inst_cream->t     = BITS(inst, 12, 15);
	/* VFP variant of instruction */
	inst_cream->esize = 32;
	inst_cream->index = BIT(inst, 21);
   
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;
		
		VFP_DEBUG_UNIMPLEMENTED(VMOVBCR);
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_MCR_TRANS
if (CoProc == 11 && CRm == 0)
{
	VFP_DEBUG_UNIMPLEMENTED(VMOVBCR);
	return ARMul_DONE;
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* MRRC / MCRR instructions */
/* cond 1100 0101 Rt2- Rt-- copr opc1 CRm- MRRC */
/* cond 1100 0100 Rt2- Rt-- copr opc1 CRm- MCRR */

/* ----------------------------------------------------------------------- */
/* VMOVBRRSS between 2 registers to 2 singles */
/* cond 1100 010X Rt2- Rt-- 1010 00X1 Vm-- */
/* cond 1100 0101 Rt2- Rt-- copr opc1 CRm- MRRC */
#define vfpinstr 	vmovbrrss
#define vfpinstr_inst 	vmovbrrss_inst
#define VFPLABEL_INST 	VMOVBRRSS_INST
#ifdef VFP_DECODE
{"vmovbrrss",    3,    ARMVFP2,    21, 27, 0x62,    8, 11, 0xA,    4, 4, 1},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vmovbrrss",    0,    ARMVFP2,    0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vmovbrrss_inst {
	unsigned int to_arm;
	unsigned int t;
	unsigned int t2;
	unsigned int m;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx     = index;
	inst_base->br     = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->to_arm     = BIT(inst, 20) == 1;
	inst_cream->t          = BITS(inst, 12, 15);
	inst_cream->t2         = BITS(inst, 16, 19);
	inst_cream->m          = BITS(inst, 0, 3)<<1|BIT(inst, 5);
   
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;
		
		VFP_DEBUG_UNIMPLEMENTED(VMOVBRRSS);
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_MCRR_TRANS
if (CoProc == 10 && (OPC_1 & 0xD) == 1)
{
	VFP_DEBUG_UNIMPLEMENTED(VMOVBRRSS);
	return ARMul_DONE;
}
#endif
#ifdef VFP_MRRC_TRANS
if (CoProc == 10 && (OPC_1 & 0xD) == 1)
{
	VFP_DEBUG_UNIMPLEMENTED(VMOVBRRSS);
	return ARMul_DONE;
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VMOVBRRD between 2 registers and 1 double */
/* cond 1100 010X Rt2- Rt-- 1011 00X1 Vm-- */
/* cond 1100 0101 Rt2- Rt-- copr opc1 CRm- MRRC */
#define vfpinstr 	vmovbrrd
#define vfpinstr_inst 	vmovbrrd_inst
#define VFPLABEL_INST 	VMOVBRRD_INST
#ifdef VFP_DECODE
{"vmovbrrd",    3,    ARMVFP2,    21, 27, 0x62,    6, 11, 0x2c,    4, 4, 1},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vmovbrrd",    0,    ARMVFP2,    0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vmovbrrd_inst {
	unsigned int to_arm;
	unsigned int t;
	unsigned int t2;
	unsigned int m;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx     = index;
	inst_base->br     = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->to_arm   = BIT(inst, 20) == 1;
	inst_cream->t        = BITS(inst, 12, 15);
	inst_cream->t2       = BITS(inst, 16, 19);
	inst_cream->m        = BIT(inst, 5)<<4 | BITS(inst, 0, 3);

	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;
		
		VMOVBRRD(cpu, inst_cream->to_arm, inst_cream->t, inst_cream->t2, inst_cream->m, 
				&(cpu->Reg[inst_cream->t]), &(cpu->Reg[inst_cream->t2]));
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_MCRR_TRANS
if (CoProc == 11 && (OPC_1 & 0xD) == 1)
{
	/* Transfering Rt and Rt2 is not mandatory, as the value of interest is pointed by value1 and value2 */
	VMOVBRRD(state, BIT(20), Rt, Rt2, BIT(5)<<4|CRm, &value1, &value2);
	return ARMul_DONE;
}
#endif
#ifdef VFP_MRRC_TRANS
if (CoProc == 11 && (OPC_1 & 0xD) == 1)
{
	/* Transfering Rt and Rt2 is not mandatory, as the value of interest is pointed by value1 and value2 */
	VMOVBRRD(state, BIT(20), Rt, Rt2, BIT(5)<<4|CRm, value1, value2);
	return ARMul_DONE;
}
#endif
#ifdef VFP_MRRC_IMPL
void VMOVBRRD(ARMul_State * state, ARMword to_arm, ARMword t, ARMword t2, ARMword n, ARMword *value1, ARMword *value2)
{
	DBG("VMOV(BRRD) :\n");
	if (to_arm)
	{
		DBG("\tr[%d-%d] <= s[%d-%d]=[%x-%x]\n", t2, t, n*2+1, n*2, state->ExtReg[n*2+1], state->ExtReg[n*2]);
		*value2 = state->ExtReg[n*2+1];
		*value1 = state->ExtReg[n*2];
	}
	else
	{
		DBG("\ts[%d-%d] <= r[%d-%d]=[%x-%x]\n", n*2+1, n*2, t2, t, *value2, *value1);
		state->ExtReg[n*2+1] = *value2;
		state->ExtReg[n*2] = *value1;
	}
}

#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* LDC/STC between 2 registers and 1 double */
/* cond 110X XXX1 Rn-- CRd- copr imm- imm- LDC */
/* cond 110X XXX0 Rn-- CRd- copr imm8 imm8 STC */

/* ----------------------------------------------------------------------- */
/* VSTR */
/* cond 1101 UD00 Rn-- Vd-- 101X imm8 imm8 */
#define vfpinstr 	vstr
#define vfpinstr_inst 	vstr_inst
#define VFPLABEL_INST 	VSTR_INST
#ifdef VFP_DECODE
{"vstr",        3,      ARMVFP2,        24, 27, 0xd,   20, 21, 0,       9, 11, 0x5},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vstr",    0,    ARMVFP2,    0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vstr_inst {
	unsigned int single;
	unsigned int n;
	unsigned int d;
	unsigned int imm32;
	unsigned int add;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;
	
	inst_cream->single = BIT(inst, 8) == 0;
	inst_cream->add	   = BIT(inst, 23);
	inst_cream->imm32  = BITS(inst, 0,7) << 2;
	inst_cream->d      = (inst_cream->single ? BITS(inst, 12, 15)<<1|BIT(inst, 22) : BITS(inst, 12, 15)|BIT(inst, 22)<<4);
	inst_cream->n	   = BITS(inst, 16, 19);

	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;
		
		unsigned int base = (inst_cream->n == 15 ? (cpu->Reg[inst_cream->n] & 0xFFFFFFFC) + 8 : cpu->Reg[inst_cream->n]);
		addr = (inst_cream->add ? base + inst_cream->imm32 : base - inst_cream->imm32);
		DBG("VSTR :\n");
		
		
		if (inst_cream->single)
		{
			fault = check_address_validity(cpu, addr, &phys_addr, 0);
			if (fault) goto MMU_EXCEPTION;
			fault = interpreter_write_memory(core, addr, phys_addr, cpu->ExtReg[inst_cream->d], 32);
			if (fault) goto MMU_EXCEPTION;
			DBG("\taddr[%x] <= s%d=[%x]\n", addr, inst_cream->d, cpu->ExtReg[inst_cream->d]);
		}
		else
		{
			fault = check_address_validity(cpu, addr, &phys_addr, 0);
			if (fault) goto MMU_EXCEPTION;

			/* Check endianness */
			fault = interpreter_write_memory(core, addr, phys_addr, cpu->ExtReg[inst_cream->d*2], 32);
			if (fault) goto MMU_EXCEPTION;

			fault = check_address_validity(cpu, addr + 4, &phys_addr, 0);
			if (fault) goto MMU_EXCEPTION;

			fault = interpreter_write_memory(core, addr + 4, phys_addr, cpu->ExtReg[inst_cream->d*2+1], 32);
			if (fault) goto MMU_EXCEPTION;
			DBG("\taddr[%x-%x] <= s[%d-%d]=[%x-%x]\n", addr+4, addr, inst_cream->d*2+1, inst_cream->d*2, cpu->ExtReg[inst_cream->d*2+1], cpu->ExtReg[inst_cream->d*2]);
		}
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_STC_TRANS
if (P == 1 && W == 0)
{
	return VSTR(state, type, instr, value);
}
#endif
#ifdef VFP_STC_IMPL
int VSTR(ARMul_State * state, int type, ARMword instr, ARMword * value)
{
	static int i = 0;
	static int single_reg, add, d, n, imm32, regs;
	if (type == ARMul_FIRST)
	{
		single_reg = BIT(8) == 0;	/* Double precision */
		add = BIT(23);		/* */
		imm32 = BITS(0,7)<<2;	/* may not be used */
		d = single_reg ? BITS(12, 15)<<1|BIT(22) : BIT(22)<<4|BITS(12, 15); /* Base register */
		n = BITS(16, 19);	/* destination register */
		
		DBG("VSTR :\n");
		
		i = 0;
		regs = 1;
		
		return ARMul_DONE;
	}
	else if (type == ARMul_DATA)
	{
		if (single_reg)
		{
			*value = state->ExtReg[d+i];
			DBG("\taddr[?] <= s%d=[%x]\n", d+i, state->ExtReg[d+i]);
			i++;
			if (i < regs)
				return ARMul_INC;
			else
				return ARMul_DONE;
		}
		else
		{
			/* FIXME Careful of endianness, may need to rework this */
			*value = state->ExtReg[d*2+i];
			DBG("\taddr[?] <= s[%d]=[%x]\n", d*2+i, state->ExtReg[d*2+i]);
			i++;
			if (i < regs*2)
				return ARMul_INC;
			else
				return ARMul_DONE;
		}
	}

	return -1;
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VPUSH */
/* cond 1101 0D10 1101 Vd-- 101X imm8 imm8 */
#define vfpinstr 	vpush
#define vfpinstr_inst 	vpush_inst
#define VFPLABEL_INST 	VPUSH_INST
#ifdef VFP_DECODE
{"vpush",       3,      ARMVFP2,        23, 27, 0x1a,  16, 21, 0x2d,    9, 11, 0x5},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vpush",    0,    ARMVFP2,    0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vpush_inst {
	unsigned int single;
	unsigned int d;
	unsigned int imm32;
	unsigned int regs;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx     = index;
	inst_base->br     = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->single  = BIT(inst, 8) == 0;
	inst_cream->d       = (inst_cream->single ? BITS(inst, 12, 15)<<1|BIT(inst, 22) : BITS(inst, 12, 15)|BIT(inst, 22)<<4);
	inst_cream->imm32   = BITS(inst, 0, 7)<<2;
	inst_cream->regs    = (inst_cream->single ? BITS(inst, 0, 7) : BITS(inst, 1, 7));

	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
				
		int i;

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

		DBG("VPUSH :\n");
			
		addr = cpu->Reg[R13] - inst_cream->imm32;


		for (i = 0; i < inst_cream->regs; i++)
		{
			if (inst_cream->single)
			{
				fault = check_address_validity(cpu, addr, &phys_addr, 0);
				if (fault) goto MMU_EXCEPTION;
				fault = interpreter_write_memory(core, addr, phys_addr, cpu->ExtReg[inst_cream->d+i], 32);
				if (fault) goto MMU_EXCEPTION;
				DBG("\taddr[%x] <= s%d=[%x]\n", addr, inst_cream->d+i, cpu->ExtReg[inst_cream->d+i]);
				addr += 4;
			}
			else
			{
				/* Careful of endianness, little by default */
				fault = check_address_validity(cpu, addr, &phys_addr, 0);
				if (fault) goto MMU_EXCEPTION;
				fault = interpreter_write_memory(core, addr, phys_addr, cpu->ExtReg[(inst_cream->d+i)*2], 32);
				if (fault) goto MMU_EXCEPTION;

				fault = check_address_validity(cpu, addr + 4, &phys_addr, 0);
				if (fault) goto MMU_EXCEPTION;
				fault = interpreter_write_memory(core, addr + 4, phys_addr, cpu->ExtReg[(inst_cream->d+i)*2 + 1], 32);
				if (fault) goto MMU_EXCEPTION;
				DBG("\taddr[%x-%x] <= s[%d-%d]=[%x-%x]\n", addr+4, addr, (inst_cream->d+i)*2+1, (inst_cream->d+i)*2, cpu->ExtReg[(inst_cream->d+i)*2+1], cpu->ExtReg[(inst_cream->d+i)*2]);
				addr += 8;
			}
		}
		DBG("\tsp[%x]", cpu->Reg[R13]);
		cpu->Reg[R13] = cpu->Reg[R13] - inst_cream->imm32;
		DBG("=>[%x]\n", cpu->Reg[R13]);
	
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vpush_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_STC_TRANS
if (P == 1 && U == 0 && W == 1 && Rn == 0xD)
{
	return VPUSH(state, type, instr, value);
}
#endif
#ifdef VFP_STC_IMPL
int VPUSH(ARMul_State * state, int type, ARMword instr, ARMword * value)
{
	static int i = 0;
	static int single_regs, add, wback, d, n, imm32, regs;
	if (type == ARMul_FIRST)
	{
		single_regs = BIT(8) == 0;	/* Single precision */
		d = single_regs ? BITS(12, 15)<<1|BIT(22) : BIT(22)<<4|BITS(12, 15); /* Base register */
		imm32 = BITS(0,7)<<2;	/* may not be used */
		regs = single_regs ? BITS(0, 7) : BITS(1, 7); /* FSTMX if regs is odd */

		DBG("VPUSH :\n");
		DBG("\tsp[%x]", state->Reg[R13]);
		state->Reg[R13] = state->Reg[R13] - imm32;
		DBG("=>[%x]\n", state->Reg[R13]);
		
		i = 0;
		
		return ARMul_DONE;
	} 
	else if (type == ARMul_DATA)
	{
		if (single_regs)
		{
			*value = state->ExtReg[d + i];
			DBG("\taddr[?] <= s%d=[%x]\n", d+i, state->ExtReg[d + i]);
			i++;
			if (i < regs)
				return ARMul_INC;
			else
				return ARMul_DONE;
		}
		else
		{
			/* FIXME Careful of endianness, may need to rework this */
			*value = state->ExtReg[d*2 + i];
			DBG("\taddr[?] <= s[%d]=[%x]\n", d*2 + i, state->ExtReg[d*2 + i]);
			i++;
			if (i < regs*2)
				return ARMul_INC;
			else
				return ARMul_DONE;
		}
	}

	return -1;
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VSTM */
/* cond 110P UDW0 Rn-- Vd-- 101X imm8 imm8 */
#define vfpinstr 	vstm
#define vfpinstr_inst 	vstm_inst
#define VFPLABEL_INST 	VSTM_INST
#ifdef VFP_DECODE
{"vstm",	3,	ARMVFP2,	25, 27, 0x6,	20, 20, 0,	9, 11, 0x5},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vstm",	0,	ARMVFP2,	0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vstm_inst {
	unsigned int single;
	unsigned int add;
	unsigned int wback;
	unsigned int d;
	unsigned int n;
	unsigned int imm32;
	unsigned int regs;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx     = index;
	inst_base->br     = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->single = BIT(inst, 8) == 0;
	inst_cream->add    = BIT(inst, 23);
	inst_cream->wback  = BIT(inst, 21);
	inst_cream->d      = (inst_cream->single ? BITS(inst, 12, 15)<<1|BIT(inst, 22) : BITS(inst, 12, 15)|BIT(inst, 22)<<4);
	inst_cream->n      = BITS(inst, 16, 19);
	inst_cream->imm32  = BITS(inst, 0, 7)<<2;
	inst_cream->regs   = (inst_cream->single ? BITS(inst, 0, 7) : BITS(inst, 1, 7));

	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST: /* encoding 1 */
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		int i;
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;
		
		addr = (inst_cream->add ? cpu->Reg[inst_cream->n] : cpu->Reg[inst_cream->n] - inst_cream->imm32);
		DBG("VSTM : addr[%x]\n", addr);
		
		
		for (i = 0; i < inst_cream->regs; i++)
		{
			if (inst_cream->single)
			{
				fault = check_address_validity(cpu, addr, &phys_addr, 0);
				if (fault) goto MMU_EXCEPTION;

				fault = interpreter_write_memory(core, addr, phys_addr, cpu->ExtReg[inst_cream->d+i], 32);
				if (fault) goto MMU_EXCEPTION;
				DBG("\taddr[%x] <= s%d=[%x]\n", addr, inst_cream->d+i, cpu->ExtReg[inst_cream->d+i]);
				addr += 4;
			}
			else
			{
				/* Careful of endianness, little by default */
				fault = check_address_validity(cpu, addr, &phys_addr, 0);
				if (fault) goto MMU_EXCEPTION;

				fault = interpreter_write_memory(core, addr, phys_addr, cpu->ExtReg[(inst_cream->d+i)*2], 32);
				if (fault) goto MMU_EXCEPTION;

				fault = check_address_validity(cpu, addr + 4, &phys_addr, 0);
				if (fault) goto MMU_EXCEPTION;

				fault = interpreter_write_memory(core, addr + 4, phys_addr, cpu->ExtReg[(inst_cream->d+i)*2 + 1], 32);
				if (fault) goto MMU_EXCEPTION;
				DBG("\taddr[%x-%x] <= s[%d-%d]=[%x-%x]\n", addr+4, addr, (inst_cream->d+i)*2+1, (inst_cream->d+i)*2, cpu->ExtReg[(inst_cream->d+i)*2+1], cpu->ExtReg[(inst_cream->d+i)*2]);
				addr += 8;
			}
		}
		if (inst_cream->wback){
			cpu->Reg[inst_cream->n] = (inst_cream->add ? cpu->Reg[inst_cream->n] + inst_cream->imm32 : 
						   cpu->Reg[inst_cream->n] - inst_cream->imm32);
			DBG("\twback r%d[%x]\n", inst_cream->n, cpu->Reg[inst_cream->n]);
		}

	}
	cpu->Reg[15] += 4;
	INC_PC(sizeof(vstm_inst));
cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));

	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_STC_TRANS
/* Should be the last operation of STC */
return VSTM(state, type, instr, value);
#endif
#ifdef VFP_STC_IMPL
int VSTM(ARMul_State * state, int type, ARMword instr, ARMword * value)
{
	static int i = 0;
	static int single_regs, add, wback, d, n, imm32, regs;
	if (type == ARMul_FIRST)
	{
		single_regs = BIT(8) == 0;	/* Single precision */
		add = BIT(23);		/* */
		wback = BIT(21);	/* write-back */
		d = single_regs ? BITS(12, 15)<<1|BIT(22) : BIT(22)<<4|BITS(12, 15); /* Base register */
		n = BITS(16, 19);	/* destination register */
		imm32 = BITS(0,7) * 4;	/* may not be used */
		regs = single_regs ? BITS(0, 7) : BITS(0, 7)>>1; /* FSTMX if regs is odd */

		DBG("VSTM :\n");
		
		if (wback) {
			state->Reg[n] = (add ? state->Reg[n] + imm32 : state->Reg[n] - imm32);
			DBG("\twback r%d[%x]\n", n, state->Reg[n]);
		}
		
		i = 0;
		
		return ARMul_DONE;
	} 
	else if (type == ARMul_DATA)
	{
		if (single_regs)
		{
			*value = state->ExtReg[d + i];
			DBG("\taddr[?] <= s%d=[%x]\n", d+i, state->ExtReg[d + i]);
			i++;
			if (i < regs)
				return ARMul_INC;
			else
				return ARMul_DONE;
		}
		else
		{
			/* FIXME Careful of endianness, may need to rework this */
			*value = state->ExtReg[d*2 + i];
			DBG("\taddr[?] <= s[%d]=[%x]\n", d*2 + i, state->ExtReg[d*2 + i]);
			i++;
			if (i < regs*2)
				return ARMul_INC;
			else
				return ARMul_DONE;
		}
	}

	return -1;
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	//DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	//arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	if (BIT(15)) {
		arm_tag_branch(cpu, pc, instr, tag, new_pc, next_pc);
		*new_pc = NEW_PC_NONE;
		if (BITS(25, 27) == 4 && BIT(22) == 1 && BIT(20) == 1 && BIT(15) == 1) {
			*tag |= TAG_TRAP;
		}
	} else {
		arm_tag_continue(cpu, pc, instr, tag, new_pc, next_pc);
	}
	*tag |= TAG_MEMORY;
	if(instr >> 28 != 0xe)
		*tag |= TAG_CONDITIONAL;

	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	//arch_arm_undef(cpu, bb, instr);
	int single = BIT(8) == 0;
	int add    = BIT(23);
	int wback  = BIT(21);
	int d      = single ? BITS(12, 15)<<1|BIT(22) : BITS(12, 15)|BIT(22)<<4;
	int n      = BITS(16, 19);
	int imm32  = BITS(0, 7)<<2;
	int regs   = single ? BITS(0, 7) : BITS(1, 7);

	Value* Addr = SELECT(CONST1(add), R(n), SUB(R(n), CONST(imm32)));
	//DBG("VSTM : addr[%x]\n", addr);
	int i;	
	for (i = 0; i < regs; i++)
	{
		if (single)
		{
			
			//fault = interpreter_write_memory(core, addr, phys_addr, cpu->ExtReg[inst_cream->d+i], 32);
			/* if R(i) is R15? */
			arch_write_memory(cpu, bb, Addr, RSPR(d + i), 32);
			//if (fault) goto MMU_EXCEPTION;
			//DBG("\taddr[%x] <= s%d=[%x]\n", addr, inst_cream->d+i, cpu->ExtReg[inst_cream->d+i]);
			Addr = ADD(Addr, CONST(4));
		}
		else
		{
		
			//fault = interpreter_write_memory(core, addr, phys_addr, cpu->ExtReg[(inst_cream->d+i)*2], 32);
			arch_write_memory(cpu, bb, Addr, RSPR((d + i) * 2), 32);
			//if (fault) goto MMU_EXCEPTION;

			//fault = interpreter_write_memory(core, addr + 4, phys_addr, cpu->ExtReg[(inst_cream->d+i)*2 + 1], 32);
			arch_write_memory(cpu, bb, Addr, RSPR((d + i) * 2 + 1), 32);
			//if (fault) goto MMU_EXCEPTION;
			//DBG("\taddr[%x-%x] <= s[%d-%d]=[%x-%x]\n", addr+4, addr, (inst_cream->d+i)*2+1, (inst_cream->d+i)*2, cpu->ExtReg[(inst_cream->d+i)*2+1], cpu->ExtReg[(inst_cream->d+i)*2]);
			//addr += 8;
			Addr = ADD(Addr, CONST(8));
		}
	}
	if (wback){
		//cpu->Reg[n] = (add ? cpu->Reg[n] + imm32 : 
		//			   cpu->Reg[n] - imm32);
		LETS(n, SELECT(CONST1(add), ADD(R(n), CONST(imm32)), SUB(R(n), CONST(imm32))));
		//DBG("\twback r%d[%x]\n", inst_cream->n, cpu->Reg[inst_cream->n]);
	}
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VPOP */
/* cond 1100 1D11 1101 Vd-- 101X imm8 imm8 */
#define vfpinstr 	vpop
#define vfpinstr_inst 	vpop_inst
#define VFPLABEL_INST 	VPOP_INST
#ifdef VFP_DECODE
{"vpop",        3,      ARMVFP2,        23, 27, 0x19,  16, 21, 0x3d,    9, 11, 0x5},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vpop",    0,    ARMVFP2,    0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vpop_inst {
	unsigned int single;
	unsigned int d;
	unsigned int imm32;
	unsigned int regs;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->single  = BIT(inst, 8) == 0;
	inst_cream->d       = (inst_cream->single ? BITS(inst, 12, 15)<<1|BIT(inst, 22) : BITS(inst, 12, 15)|BIT(inst, 22)<<4);
	inst_cream->imm32   = BITS(inst, 0, 7)<<2;
	inst_cream->regs    = (inst_cream->single ? BITS(inst, 0, 7) : BITS(inst, 1, 7));
	
	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		int i;
		unsigned int value1, value2;

		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;
		
		DBG("VPOP :\n");
		
		addr = cpu->Reg[R13];
		

		for (i = 0; i < inst_cream->regs; i++)
		{
			if (inst_cream->single)
			{
				fault = check_address_validity(cpu, addr, &phys_addr, 1);
				if (fault) goto MMU_EXCEPTION;

				fault = interpreter_read_memory(core, addr, phys_addr, value1, 32);
				if (fault) goto MMU_EXCEPTION;
				DBG("\ts%d <= [%x] addr[%x]\n", inst_cream->d+i, value1, addr);
				cpu->ExtReg[inst_cream->d+i] = value1;
				addr += 4;
			}
			else
			{
				/* Careful of endianness, little by default */
				fault = check_address_validity(cpu, addr, &phys_addr, 1);
				if (fault) goto MMU_EXCEPTION;

				fault = interpreter_read_memory(core, addr, phys_addr, value1, 32);
				if (fault) goto MMU_EXCEPTION;

				fault = check_address_validity(cpu, addr + 4, &phys_addr, 1);
				if (fault) goto MMU_EXCEPTION;

				fault = interpreter_read_memory(core, addr + 4, phys_addr, value2, 32);
				if (fault) goto MMU_EXCEPTION;
				DBG("\ts[%d-%d] <= [%x-%x] addr[%x-%x]\n", (inst_cream->d+i)*2+1, (inst_cream->d+i)*2, value2, value1, addr+4, addr);
				cpu->ExtReg[(inst_cream->d+i)*2] = value1;
				cpu->ExtReg[(inst_cream->d+i)*2 + 1] = value2;
				addr += 8;
			}
		}
		DBG("\tsp[%x]", cpu->Reg[R13]);
		cpu->Reg[R13] = cpu->Reg[R13] + inst_cream->imm32;
		DBG("=>[%x]\n", cpu->Reg[R13]);
		
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vpop_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_LDC_TRANS
if (P == 0 && U == 1 && W == 1 && Rn == 0xD)
{
	return VPOP(state, type, instr, value);
}
#endif
#ifdef VFP_LDC_IMPL
int VPOP(ARMul_State * state, int type, ARMword instr, ARMword value)
{
	static int i = 0;
	static int single_regs, add, wback, d, n, imm32, regs;
	if (type == ARMul_FIRST)
	{
		single_regs = BIT(8) == 0;	/* Single precision */
		d = single_regs ? BITS(12, 15)<<1|BIT(22) : BIT(22)<<4|BITS(12, 15); /* Base register */
		imm32 = BITS(0,7)<<2;	/* may not be used */
		regs = single_regs ? BITS(0, 7) : BITS(1, 7); /* FLDMX if regs is odd */

		DBG("VPOP :\n");
		DBG("\tsp[%x]", state->Reg[R13]);
		state->Reg[R13] = state->Reg[R13] + imm32;
		DBG("=>[%x]\n", state->Reg[R13]);
		
		i = 0;
		
		return ARMul_DONE;
	}
	else if (type == ARMul_TRANSFER)
	{
		return ARMul_DONE;
	}
	else if (type == ARMul_DATA)
	{
		if (single_regs)
		{
			state->ExtReg[d + i] = value;
			DBG("\ts%d <= [%x]\n", d + i, value);
			i++;
			if (i < regs)
				return ARMul_INC;
			else
				return ARMul_DONE;
		}
		else
		{
			/* FIXME Careful of endianness, may need to rework this */
			state->ExtReg[d*2 + i] = value;
			DBG("\ts%d <= [%x]\n", d*2 + i, value);
			i++;
			if (i < regs*2)
				return ARMul_INC;
			else
				return ARMul_DONE;
		}
	}

	return -1;
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);

	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VLDR */
/* cond 1101 UD01 Rn-- Vd-- 101X imm8 imm8 */
#define vfpinstr 	vldr
#define vfpinstr_inst 	vldr_inst
#define VFPLABEL_INST 	VLDR_INST
#ifdef VFP_DECODE
{"vldr",        3,      ARMVFP2,        24, 27, 0xd,   20, 21, 0x1,     9, 11, 0x5},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vldr",    0,    ARMVFP2,    0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vldr_inst {
	unsigned int single;
	unsigned int n;
	unsigned int d;
	unsigned int imm32;
	unsigned int add;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx	 = index;
	inst_base->br	 = NON_BRANCH;
	inst_base->load_r15 = 0;
	
	inst_cream->single = BIT(inst, 8) == 0;
	inst_cream->add	   = BIT(inst, 23);
	inst_cream->imm32  = BITS(inst, 0,7) << 2;
	inst_cream->d      = (inst_cream->single ? BITS(inst, 12, 15)<<1|BIT(inst, 22) : BITS(inst, 12, 15)|BIT(inst, 22)<<4);
	inst_cream->n	   = BITS(inst, 16, 19);

	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;
		
		unsigned int base = (inst_cream->n == 15 ? (cpu->Reg[inst_cream->n] & 0xFFFFFFFC) + 8 : cpu->Reg[inst_cream->n]);
		addr = (inst_cream->add ? base + inst_cream->imm32 : base - inst_cream->imm32);
		DBG("VLDR :\n", addr);
		
		
		if (inst_cream->single)
		{
			fault = check_address_validity(cpu, addr, &phys_addr, 1);
			if (fault) goto MMU_EXCEPTION;
			fault = interpreter_read_memory(core, addr, phys_addr, cpu->ExtReg[inst_cream->d], 32);
			if (fault) goto MMU_EXCEPTION;
			DBG("\ts%d <= [%x] addr[%x]\n", inst_cream->d, cpu->ExtReg[inst_cream->d], addr);
		}
		else
		{
			unsigned int word1, word2;
			fault = check_address_validity(cpu, addr, &phys_addr, 1);
			if (fault) goto MMU_EXCEPTION;
			fault = interpreter_read_memory(core, addr, phys_addr, word1, 32);
			if (fault) goto MMU_EXCEPTION;

			fault = check_address_validity(cpu, addr + 4, &phys_addr, 1);
			if (fault) goto MMU_EXCEPTION;
			fault = interpreter_read_memory(core, addr + 4, phys_addr, word2, 32);
			if (fault) goto MMU_EXCEPTION;
			/* Check endianness */
			cpu->ExtReg[inst_cream->d*2] = word1;
			cpu->ExtReg[inst_cream->d*2+1] = word2;
			DBG("\ts[%d-%d] <= [%x-%x] addr[%x-%x]\n", inst_cream->d*2+1, inst_cream->d*2, word2, word1, addr+4, addr);
		}
	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vldr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_LDC_TRANS
if (P == 1 && W == 0)
{
	return VLDR(state, type, instr, value);
}
#endif
#ifdef VFP_LDC_IMPL
int VLDR(ARMul_State * state, int type, ARMword instr, ARMword value)
{
	static int i = 0;
	static int single_reg, add, d, n, imm32, regs;
	if (type == ARMul_FIRST)
	{
		single_reg = BIT(8) == 0;	/* Double precision */
		add = BIT(23);		/* */
		imm32 = BITS(0,7)<<2;	/* may not be used */
		d = single_reg ? BITS(12, 15)<<1|BIT(22) : BIT(22)<<4|BITS(12, 15); /* Base register */
		n = BITS(16, 19);	/* destination register */
		
		DBG("VLDR :\n");
		
		i = 0;
		regs = 1;
		
		return ARMul_DONE;
	}
	else if (type == ARMul_TRANSFER)
	{
		return ARMul_DONE;
	}
	else if (type == ARMul_DATA)
	{
		if (single_reg)
		{
			state->ExtReg[d+i] = value;
			DBG("\ts%d <= [%x]\n", d+i, value);
			i++;
			if (i < regs)
				return ARMul_INC;
			else
				return ARMul_DONE;
		}
		else
		{
			/* FIXME Careful of endianness, may need to rework this */
			state->ExtReg[d*2+i] = value;
			DBG("\ts[%d] <= [%x]\n", d*2+i, value);
			i++;
			if (i < regs*2)
				return ARMul_INC;
			else
				return ARMul_DONE;
		}
	}

	return -1;
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

/* ----------------------------------------------------------------------- */
/* VLDM */
/* cond 110P UDW1 Rn-- Vd-- 101X imm8 imm8 */
#define vfpinstr 	vldm
#define vfpinstr_inst 	vldm_inst
#define VFPLABEL_INST 	VLDM_INST
#ifdef VFP_DECODE
{"vldm",	3,	ARMVFP2,	25, 27, 0x6,	20, 20, 1,	9, 11, 0x5},
#endif
#ifdef VFP_DECODE_EXCLUSION
{"vldm",	0,	ARMVFP2,	0},
#endif
#ifdef VFP_INTERPRETER_TABLE
INTERPRETER_TRANSLATE(vfpinstr),
#endif
#ifdef VFP_INTERPRETER_LABEL
&&VFPLABEL_INST,
#endif
#ifdef VFP_INTERPRETER_STRUCT
typedef struct _vldm_inst {
	unsigned int single;
	unsigned int add;
	unsigned int wback;
	unsigned int d;
	unsigned int n;
	unsigned int imm32;
	unsigned int regs;
} vfpinstr_inst;
#endif
#ifdef VFP_INTERPRETER_TRANS
ARM_INST_PTR INTERPRETER_TRANSLATE(vfpinstr)(unsigned int inst, int index)
{
	VFP_DEBUG_TRANSLATE;
	
	arm_inst *inst_base = (arm_inst *)AllocBuffer(sizeof(arm_inst) + sizeof(vfpinstr_inst));
	vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;

	inst_base->cond  = BITS(inst, 28, 31);
	inst_base->idx     = index;
	inst_base->br     = NON_BRANCH;
	inst_base->load_r15 = 0;

	inst_cream->single = BIT(inst, 8) == 0;
	inst_cream->add    = BIT(inst, 23);
	inst_cream->wback  = BIT(inst, 21);
	inst_cream->d      = (inst_cream->single ? BITS(inst, 12, 15)<<1|BIT(inst, 22) : BITS(inst, 12, 15)|BIT(inst, 22)<<4);
	inst_cream->n      = BITS(inst, 16, 19);
	inst_cream->imm32  = BITS(inst, 0, 7)<<2;
	inst_cream->regs   = (inst_cream->single ? BITS(inst, 0, 7) : BITS(inst, 1, 7));

	return inst_base;
}
#endif
#ifdef VFP_INTERPRETER_IMPL
VFPLABEL_INST:
{
	INC_ICOUNTER;
	if ((inst_base->cond == 0xe) || CondPassed(cpu, inst_base->cond)) {
		CHECK_VFP_ENABLED;
		
		int i;
		
		vfpinstr_inst *inst_cream = (vfpinstr_inst *)inst_base->component;
		
		addr = (inst_cream->add ? cpu->Reg[inst_cream->n] : cpu->Reg[inst_cream->n] - inst_cream->imm32);
		DBG("VLDM : addr[%x]\n", addr);
		
		for (i = 0; i < inst_cream->regs; i++)
		{
			if (inst_cream->single)
			{
				fault = check_address_validity(cpu, addr, &phys_addr, 1);
				if (fault) goto MMU_EXCEPTION;
				fault = interpreter_read_memory(core, addr, phys_addr, cpu->ExtReg[inst_cream->d+i], 32);
				if (fault) goto MMU_EXCEPTION;
				DBG("\ts%d <= [%x] addr[%x]\n", inst_cream->d+i, cpu->ExtReg[inst_cream->d+i], addr);
				addr += 4;
			}
			else
			{
				/* Careful of endianness, little by default */
				fault = check_address_validity(cpu, addr, &phys_addr, 1);
				if (fault) goto MMU_EXCEPTION;
				fault = interpreter_read_memory(core, addr, phys_addr, cpu->ExtReg[(inst_cream->d+i)*2], 32);
				if (fault) goto MMU_EXCEPTION;

				fault = check_address_validity(cpu, addr + 4, &phys_addr, 1);
				if (fault) goto MMU_EXCEPTION;
				fault = interpreter_read_memory(core, addr + 4, phys_addr, cpu->ExtReg[(inst_cream->d+i)*2 + 1], 32);
				if (fault) goto MMU_EXCEPTION;
				DBG("\ts[%d-%d] <= [%x-%x] addr[%x-%x]\n", (inst_cream->d+i)*2+1, (inst_cream->d+i)*2, cpu->ExtReg[(inst_cream->d+i)*2+1], cpu->ExtReg[(inst_cream->d+i)*2], addr+4, addr);
				addr += 8;
			}
		}
		if (inst_cream->wback){
			cpu->Reg[inst_cream->n] = (inst_cream->add ? cpu->Reg[inst_cream->n] + inst_cream->imm32 : 
						   cpu->Reg[inst_cream->n] - inst_cream->imm32);
			DBG("\twback r%d[%x]\n", inst_cream->n, cpu->Reg[inst_cream->n]);
		}

	}
	cpu->Reg[15] += GET_INST_SIZE(cpu);
	INC_PC(sizeof(vfpinstr_inst));
	FETCH_INST;
	GOTO_NEXT_INST;
}
#endif
#ifdef VFP_LDC_TRANS
/* Should be the last operation of LDC */
return VLDM(state, type, instr, value);
#endif
#ifdef VFP_LDC_IMPL
int VLDM(ARMul_State * state, int type, ARMword instr, ARMword value)
{
	static int i = 0;
	static int single_regs, add, wback, d, n, imm32, regs;
	if (type == ARMul_FIRST)
	{
		single_regs = BIT(8) == 0;	/* Single precision */
		add = BIT(23);		/* */
		wback = BIT(21);	/* write-back */
		d = single_regs ? BITS(12, 15)<<1|BIT(22) : BIT(22)<<4|BITS(12, 15); /* Base register */
		n = BITS(16, 19);	/* destination register */
		imm32 = BITS(0,7) * 4;	/* may not be used */
		regs = single_regs ? BITS(0, 7) : BITS(0, 7)>>1; /* FLDMX if regs is odd */

		DBG("VLDM :\n");
		
		if (wback) {
			state->Reg[n] = (add ? state->Reg[n] + imm32 : state->Reg[n] - imm32);
			DBG("\twback r%d[%x]\n", n, state->Reg[n]);
		}
		
		i = 0;
		
		return ARMul_DONE;
	} 
	else if (type == ARMul_DATA)
	{
		if (single_regs)
		{
			state->ExtReg[d + i] = value;
			DBG("\ts%d <= [%x] addr[?]\n", d+i, state->ExtReg[d + i]);
			i++;
			if (i < regs)
				return ARMul_INC;
			else
				return ARMul_DONE;
		}
		else
		{
			/* FIXME Careful of endianness, may need to rework this */
			state->ExtReg[d*2 + i] = value;
			DBG("\ts[%d] <= [%x] addr[?]\n", d*2 + i, state->ExtReg[d*2 + i]);
			i++;
			if (i < regs*2)
				return ARMul_INC;
			else
				return ARMul_DONE;
		}
	}

	return -1;
}
#endif
#ifdef VFP_DYNCOM_TABLE
DYNCOM_FILL_ACTION(vfpinstr),
#endif
#ifdef VFP_DYNCOM_TAG
int DYNCOM_TAG(vfpinstr)(cpu_t *cpu, addr_t pc, uint32_t instr, tag_t *tag, addr_t *new_pc, addr_t *next_pc)
{
	int instr_size = INSTR_SIZE;
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arm_tag_trap(cpu, pc, instr, tag, new_pc, next_pc);
	return instr_size;
}
#endif
#ifdef VFP_DYNCOM_TRANS
int DYNCOM_TRANS(vfpinstr)(cpu_t *cpu, uint32_t instr, BasicBlock *bb, addr_t pc){
	DBG("\t\tin %s instruction is not implemented.\n", __FUNCTION__);
	arch_arm_undef(cpu, bb, instr);
	return No_exp;
}
#endif
#undef vfpinstr
#undef vfpinstr_inst
#undef VFPLABEL_INST

#define VFP_DEBUG_TRANSLATE DBG("in func %s, %x\n", __FUNCTION__, inst);
#define VFP_DEBUG_UNIMPLEMENTED(x) printf("in func %s, " #x " unimplemented\n", __FUNCTION__); exit(-1);
#define VFP_DEBUG_UNTESTED(x) printf("in func %s, " #x " untested\n", __FUNCTION__);

#define CHECK_VFP_ENABLED	
	
#define CHECK_VFP_CDP_RET	vfp_raise_exceptions(ret, inst_cream->instr, cpu->VFP[VFP_FPSCR]); //if (ret == -1) {printf("VFP CDP FAILURE %x\n", inst_cream->instr); exit(-1);}
