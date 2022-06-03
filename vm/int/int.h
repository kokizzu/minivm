#pragma once

#include "gc.h"
#include "../lib.h"
#include "../opcode.h"

enum vm_int_op_t
{
  VM_INT_OP_EXIT,
  VM_INT_OP_PUTC,
  VM_INT_OP_MOV,
  VM_INT_OP_MOVC,
  VM_INT_OP_MOVF,
  VM_INT_OP_ADD,
  VM_INT_OP_SUB,
  VM_INT_OP_RET,
  VM_INT_OP_BEQ,
  VM_INT_OP_BEQC,
  VM_INT_OP_CALL0,
  VM_INT_OP_CALL1,
  VM_INT_OP_CALL2,
  VM_INT_OP_CALL3,
  VM_INT_OP_CALL4,
  VM_INT_OP_CALL5,
  VM_INT_OP_CALL6,
  VM_INT_OP_CALL7,
  VM_INT_OP_CALL8,
  VM_INT_OP_DCALL0,
  VM_INT_OP_DCALL1,
  VM_INT_OP_DCALL2,
  VM_INT_OP_DCALL3,
  VM_INT_OP_DCALL4,
  VM_INT_OP_DCALL5,
  VM_INT_OP_DCALL6,
  VM_INT_OP_DCALL7,
  VM_INT_OP_DCALL8,
  VM_INT_OP_JUMP,
  VM_INT_OP_DJUMP,
  VM_INT_OP_ADDC,
  VM_INT_OP_SUBC,
  VM_INT_OP_CSUB,
  VM_INT_OP_RETC,
  VM_INT_OP_FADD,
  VM_INT_OP_FADDC,
  VM_INT_OP_FSUB,
  VM_INT_OP_FSUBC,
  VM_INT_OP_FCSUB,
  VM_INT_OP_FMUL,
  VM_INT_OP_FMULC,
  VM_INT_OP_FDIV,
  VM_INT_OP_FDIVC,
  VM_INT_OP_FCDIV,
  VM_INT_OP_FMOD,
  VM_INT_OP_FMODC,
  VM_INT_OP_FCMOD,
  VM_INT_OP_FBB,
  VM_INT_OP_FBEQ,
  VM_INT_OP_FBLT,
  VM_INT_OP_FBEQC,
  VM_INT_OP_FBLTC,
  VM_INT_OP_FCBLT,
  VM_INT_OP_FTOS,
  VM_INT_OP_TOF,
  VM_INT_OP_MUL,
  VM_INT_OP_MULC,
  VM_INT_OP_DIV,
  VM_INT_OP_DIVC,
  VM_INT_OP_CDIV,
  VM_INT_OP_MOD,
  VM_INT_OP_MODC,
  VM_INT_OP_CMOD,
  VM_INT_OP_BB,
  VM_INT_OP_BLT,
  VM_INT_OP_BLTC,
  VM_INT_OP_CBLT,
  VM_INT_MAX_OP,
};

uint8_t *vm_int_comp(size_t nops, const vm_opcode_t *ops, uint8_t *jumps, void **ptrs, vm_gc_t *restrict gc);
int vm_int_run(size_t nops, const vm_opcode_t *iops, vm_gc_t *restrict gc);