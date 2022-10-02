
#if !defined(VM_HEADER_IR_BE_DEBUG)
#define VM_HEADER_IR_BE_DEBUG

#include "int3.h"

static inline const char *vm_int_debug_instr_name(size_t op) {
    static const char *table[] = {
        [VM_INT_OP_EXIT] = "exit",
        [VM_INT_OP_MOV_V] = "mov",
        [VM_INT_OP_MOV_B] = "mov",
        [VM_INT_OP_MOV_I] = "mov",
        [VM_INT_OP_MOV_F] = "mov",
        [VM_INT_OP_MOV_R] = "mov",
        [VM_INT_OP_MOV_T] = "mov",
        [VM_INT_OP_FMOV_R] = "fmov",
        [VM_INT_OP_I32BOR_RR] = "bor.i32",
        [VM_INT_OP_I32BOR_RI] = "bor.i32",
        [VM_INT_OP_I32BAND_RR] = "band.i32",
        [VM_INT_OP_I32BAND_RI] = "band.i32",
        [VM_INT_OP_I32BXOR_RR] = "bxor.i32",
        [VM_INT_OP_I32BXOR_RI] = "bxor.i32",
        [VM_INT_OP_I32BSHL_RR] = "bshl.i32",
        [VM_INT_OP_I32BSHL_RI] = "bshl.i32",
        [VM_INT_OP_I32BSHR_RR] = "bshr.i32",
        [VM_INT_OP_I32BSHR_RI] = "bshr.i32",
        [VM_INT_OP_I32ADD_RR] = "add.i32",
        [VM_INT_OP_I32ADD_RI] = "add.i32",
        [VM_INT_OP_I32SUB_RR] = "sub.i32",
        [VM_INT_OP_I32SUB_RI] = "sub.i32",
        [VM_INT_OP_I32SUB_IR] = "sub.i32",
        [VM_INT_OP_I32MUL_RR] = "mul.i32",
        [VM_INT_OP_I32MUL_RI] = "mul.i32",
        [VM_INT_OP_I32DIV_RR] = "div.i32",
        [VM_INT_OP_I32DIV_RI] = "div.i32",
        [VM_INT_OP_I32DIV_IR] = "div.i32",
        [VM_INT_OP_I32MOD_RR] = "mod.i32",
        [VM_INT_OP_I32MOD_RI] = "mod.i32",
        [VM_INT_OP_I32MOD_IR] = "mod.i32",
        [VM_INT_OP_I32BLT_RRLL] = "blt.i32",
        [VM_INT_OP_I32BLT_RILL] = "blt.i32",
        [VM_INT_OP_I32BLT_IRLL] = "blt.i32",
        [VM_INT_OP_I32BEQ_RRLL] = "beq.i32",
        [VM_INT_OP_I32BEQ_RILL] = "beq.i32",
        [VM_INT_OP_I32BEQ_IRLL] = "beq.i32",
        [VM_INT_OP_I32BLT_RRTT] = "blt.i32",
        [VM_INT_OP_I32BLT_RITT] = "blt.i32",
        [VM_INT_OP_I32BLT_IRTT] = "blt.i32",
        [VM_INT_OP_I32BEQ_RRTT] = "beq.i32",
        [VM_INT_OP_I32BEQ_RITT] = "beq.i32",
        [VM_INT_OP_I32BEQ_IRTT] = "beq.i32",
        [VM_INT_OP_FADD_RR] = "add.f64",
        [VM_INT_OP_FADD_RF] = "add.f64",
        [VM_INT_OP_FSUB_RR] = "sub.f64",
        [VM_INT_OP_FSUB_RF] = "sub.f64",
        [VM_INT_OP_FSUB_FR] = "sub.f64",
        [VM_INT_OP_FMUL_RR] = "mul.f64",
        [VM_INT_OP_FMUL_RF] = "mul.f64",
        [VM_INT_OP_FDIV_RR] = "div.f64",
        [VM_INT_OP_FDIV_RF] = "div.f64",
        [VM_INT_OP_FDIV_FR] = "div.f64",
        [VM_INT_OP_FMOD_RR] = "mod.f64",
        [VM_INT_OP_FMOD_RF] = "mod.f64",
        [VM_INT_OP_FMOD_FR] = "mod.f64",
        [VM_INT_OP_FBLT_RRLL] = "blt.f64",
        [VM_INT_OP_FBLT_RFLL] = "blt.f64",
        [VM_INT_OP_FBLT_FRLL] = "blt.f64",
        [VM_INT_OP_FBEQ_RRLL] = "beq.f64",
        [VM_INT_OP_FBEQ_RFLL] = "beq.f64",
        [VM_INT_OP_FBEQ_FRLL] = "beq.f64",
        [VM_INT_OP_FBLT_RRTT] = "blt.f64",
        [VM_INT_OP_FBLT_RFTT] = "blt.f64",
        [VM_INT_OP_FBLT_FRTT] = "blt.f64",
        [VM_INT_OP_FBEQ_RRTT] = "beq.f64",
        [VM_INT_OP_FBEQ_RFTT] = "beq.f64",
        [VM_INT_OP_FBEQ_FRTT] = "beq.f64",
        [VM_INT_OP_CALL_L0] = "call",
        [VM_INT_OP_CALL_L1] = "call",
        [VM_INT_OP_CALL_L2] = "call",
        [VM_INT_OP_CALL_L3] = "call",
        [VM_INT_OP_CALL_L4] = "call",
        [VM_INT_OP_CALL_L5] = "call",
        [VM_INT_OP_CALL_L6] = "call",
        [VM_INT_OP_CALL_L7] = "call",
        [VM_INT_OP_CALL_L8] = "call",
        [VM_INT_OP_CALL_R0] = "call",
        [VM_INT_OP_CALL_R1] = "call",
        [VM_INT_OP_CALL_R2] = "call",
        [VM_INT_OP_CALL_R3] = "call",
        [VM_INT_OP_CALL_R4] = "call",
        [VM_INT_OP_CALL_R5] = "call",
        [VM_INT_OP_CALL_R6] = "call",
        [VM_INT_OP_CALL_R7] = "call",
        [VM_INT_OP_CALL_R8] = "call",
        [VM_INT_OP_CALL_X0] = "call",
        [VM_INT_OP_CALL_X1] = "call",
        [VM_INT_OP_CALL_X2] = "call",
        [VM_INT_OP_CALL_X3] = "call",
        [VM_INT_OP_CALL_X4] = "call",
        [VM_INT_OP_CALL_X5] = "call",
        [VM_INT_OP_CALL_X6] = "call",
        [VM_INT_OP_CALL_X7] = "call",
        [VM_INT_OP_CALL_X8] = "call",
        [VM_INT_OP_CALL_C0] = "call",
        [VM_INT_OP_CALL_C1] = "call",
        [VM_INT_OP_CALL_C2] = "call",
        [VM_INT_OP_CALL_C3] = "call",
        [VM_INT_OP_CALL_C4] = "call",
        [VM_INT_OP_CALL_C5] = "call",
        [VM_INT_OP_CALL_C6] = "call",
        [VM_INT_OP_CALL_C7] = "call",
        [VM_INT_OP_ARR_F] = "arr",
        [VM_INT_OP_ARR_R] = "arr",
        [VM_INT_OP_SET_RRR] = "set",
        [VM_INT_OP_SET_RRI] = "set",
        [VM_INT_OP_SET_RIR] = "set",
        [VM_INT_OP_SET_RII] = "set",
        [VM_INT_OP_GET_RR] = "get",
        [VM_INT_OP_GET_RI] = "get",
        [VM_INT_OP_LEN_R] = "len",
        [VM_INT_OP_OUT_I] = "out",
        [VM_INT_OP_OUT_R] = "out",
        [VM_INT_OP_JUMP_L] = "jump",
        [VM_INT_OP_BB_RLL] = "bb",
        [VM_INT_OP_RET_I] = "ret",
        [VM_INT_OP_RET_F] = "ret",
        [VM_INT_OP_RET_RV] = "ret",
        [VM_INT_OP_RET_RB] = "ret",
        [VM_INT_OP_RET_RI] = "ret",
        [VM_INT_OP_RET_RIF] = "ret",
        [VM_INT_OP_RET_RF] = "ret",
        [VM_INT_OP_RET_RA] = "ret",
        [VM_INT_OP_RET_RT] = "ret",
        [VM_INT_OP_CALL_T0] = "call",
        [VM_INT_OP_CALL_T1] = "call",
        [VM_INT_OP_CALL_T2] = "call",
        [VM_INT_OP_CALL_T3] = "call",
        [VM_INT_OP_CALL_T4] = "call",
        [VM_INT_OP_CALL_T5] = "call",
        [VM_INT_OP_CALL_T6] = "call",
        [VM_INT_OP_CALL_T7] = "call",
        [VM_INT_OP_CALL_T8] = "call",
        [VM_INT_OP_JUMP_T] = "jump",
        [VM_INT_OP_BB_RTT] = "bb",
        [VM_INT_OP_TAB] = "tab",
        [VM_INT_OP_TSET_RRR] = "set.table",
        [VM_INT_OP_TSET_RRF] = "set.table",
        [VM_INT_OP_TSET_RFR] = "set.table",
        [VM_INT_OP_TSET_RFF] = "set.table",
        [VM_INT_OP_TGET_RR] = "get.table",
        [VM_INT_OP_TGET_RF] = "get.table",
    };
    return table[op];
}

static inline const char *vm_int_debug_instr_format(size_t opcode) {
    static const char *table[] = {
        [VM_INT_OP_EXIT] = "?",
        [VM_INT_OP_MOV_V] = ":N",
        [VM_INT_OP_MOV_B] = ":B",
        [VM_INT_OP_MOV_I] = ":I",
        [VM_INT_OP_MOV_F] = ":F",
        [VM_INT_OP_MOV_R] = ":t",
        [VM_INT_OP_MOV_T] = ":T",
        [VM_INT_OP_FMOV_R] = ";i",
        [VM_INT_OP_IMOV_R] = ";f",
        [VM_INT_OP_I32BOR_RR] = ":ii",
        [VM_INT_OP_I32BOR_RI] = ":iI",
        [VM_INT_OP_I32BAND_RR] = ":ii",
        [VM_INT_OP_I32BAND_RI] = ":iI",
        [VM_INT_OP_I32BXOR_RR] = ":ii",
        [VM_INT_OP_I32BXOR_RI] = ":iI",
        [VM_INT_OP_I32BSHL_RR] = ":ii",
        [VM_INT_OP_I32BSHL_RI] = ":iI",
        [VM_INT_OP_I32BSHR_RR] = ":ii",
        [VM_INT_OP_I32BSHR_RI] = ":iI",
        [VM_INT_OP_I32ADD_RR] = ":ii",
        [VM_INT_OP_I32ADD_RI] = ":iI",
        [VM_INT_OP_I32SUB_RR] = ":ii",
        [VM_INT_OP_I32SUB_RI] = ":iI",
        [VM_INT_OP_I32SUB_IR] = ":Ii",
        [VM_INT_OP_I32MUL_RR] = ":ii",
        [VM_INT_OP_I32MUL_RI] = ":iI",
        [VM_INT_OP_I32DIV_RR] = ":ii",
        [VM_INT_OP_I32DIV_RI] = ":iI",
        [VM_INT_OP_I32DIV_IR] = ":Ii",
        [VM_INT_OP_I32MOD_RR] = ":ii",
        [VM_INT_OP_I32MOD_RI] = ":iI",
        [VM_INT_OP_I32MOD_IR] = ":Ii",
        [VM_INT_OP_I32BLT_RRLL] = "?iiLL",
        [VM_INT_OP_I32BLT_RILL] = "?iILL",
        [VM_INT_OP_I32BLT_IRLL] = "?IiLL",
        [VM_INT_OP_I32BEQ_RRLL] = "?iiLL",
        [VM_INT_OP_I32BEQ_RILL] = "?iILL",
        [VM_INT_OP_I32BEQ_IRLL] = "?IiLL",
        [VM_INT_OP_I32BLT_RRTT] = "?iiLL",
        [VM_INT_OP_I32BLT_RITT] = "?iILL",
        [VM_INT_OP_I32BLT_IRTT] = "?IiLL",
        [VM_INT_OP_I32BEQ_RRTT] = "?iiLL",
        [VM_INT_OP_I32BEQ_RITT] = "?iILL",
        [VM_INT_OP_I32BEQ_IRTT] = "?IiLL",
        [VM_INT_OP_FADD_RR] = ":ff",
        [VM_INT_OP_FADD_RF] = ":fF",
        [VM_INT_OP_FSUB_RR] = ":ff",
        [VM_INT_OP_FSUB_RF] = ":fF",
        [VM_INT_OP_FSUB_FR] = ":Ff",
        [VM_INT_OP_FMUL_RR] = ":ff",
        [VM_INT_OP_FMUL_RF] = ":fF",
        [VM_INT_OP_FDIV_RR] = ":ff",
        [VM_INT_OP_FDIV_RF] = ":fF",
        [VM_INT_OP_FDIV_FR] = ":Ff",
        [VM_INT_OP_FMOD_RR] = ":ff",
        [VM_INT_OP_FMOD_RF] = ":fF",
        [VM_INT_OP_FMOD_FR] = ":Ff",
        [VM_INT_OP_FBLT_RRLL] = "?ffLL",
        [VM_INT_OP_FBLT_RFLL] = "?fFLL",
        [VM_INT_OP_FBLT_FRLL] = "?FfLL",
        [VM_INT_OP_FBEQ_RRLL] = "?ffLL",
        [VM_INT_OP_FBEQ_RFLL] = "?fFLL",
        [VM_INT_OP_FBEQ_FRLL] = "?FfLL",
        [VM_INT_OP_FBLT_RRTT] = "?ffLL",
        [VM_INT_OP_FBLT_RFTT] = "?fFLL",
        [VM_INT_OP_FBLT_FRTT] = "?FfLL",
        [VM_INT_OP_FBEQ_RRTT] = "?ffLL",
        [VM_INT_OP_FBEQ_RFTT] = "?fIFLL",
        [VM_INT_OP_FBEQ_FRTT] = "?FfLL",
        [VM_INT_OP_CALL_L0] = "L:",
        [VM_INT_OP_CALL_L1] = "Ld:",
        [VM_INT_OP_CALL_L2] = "Ldd:",
        [VM_INT_OP_CALL_L3] = "Lddd:",
        [VM_INT_OP_CALL_L4] = "Ldddd:",
        [VM_INT_OP_CALL_L5] = "Lddddd:",
        [VM_INT_OP_CALL_L6] = "Ldddddd:",
        [VM_INT_OP_CALL_L7] = "Lddddddd:",
        [VM_INT_OP_CALL_L8] = "Ldddddddd:",
        [VM_INT_OP_CALL_R0] = "t:",
        [VM_INT_OP_CALL_R1] = "td:",
        [VM_INT_OP_CALL_R2] = "tdd:",
        [VM_INT_OP_CALL_R3] = "tddd:",
        [VM_INT_OP_CALL_R4] = "tdddd:",
        [VM_INT_OP_CALL_R5] = "tddddd:",
        [VM_INT_OP_CALL_R6] = "tdddddd:",
        [VM_INT_OP_CALL_R7] = "tddddddd:",
        [VM_INT_OP_CALL_R8] = "tdddddddd:",
        [VM_INT_OP_CALL_X0] = "X:",
        [VM_INT_OP_CALL_X1] = "Xd:",
        [VM_INT_OP_CALL_X2] = "Xdd:",
        [VM_INT_OP_CALL_X3] = "Xddd:",
        [VM_INT_OP_CALL_X4] = "Xdddd:",
        [VM_INT_OP_CALL_X5] = "Xddddd:",
        [VM_INT_OP_CALL_X6] = "Xdddddd:",
        [VM_INT_OP_CALL_X7] = "Xddddddd:",
        [VM_INT_OP_CALL_X8] = "Xdddddddd:",
        [VM_INT_OP_CALL_C0] = "c:",
        [VM_INT_OP_CALL_C1] = "cd:",
        [VM_INT_OP_CALL_C2] = "cdd:",
        [VM_INT_OP_CALL_C3] = "cddd:",
        [VM_INT_OP_CALL_C4] = "cdddd:",
        [VM_INT_OP_CALL_C5] = "cddddd:",
        [VM_INT_OP_CALL_C6] = "cdddddd:",
        [VM_INT_OP_CALL_C7] = "cddddddd:",
        [VM_INT_OP_ARR_F] = ":F",
        [VM_INT_OP_ARR_R] = ":f",
        [VM_INT_OP_SET_RRR] = "afd",
        [VM_INT_OP_SET_RRI] = "afF",
        [VM_INT_OP_SET_RIR] = "aFd",
        [VM_INT_OP_SET_RII] = "aFF",
        [VM_INT_OP_GET_RR] = ":af",
        [VM_INT_OP_GET_RI] = ":aF",
        [VM_INT_OP_LEN_R] = ":a",
        [VM_INT_OP_OUT_I] = ".I",
        [VM_INT_OP_OUT_R] = ".i",
        [VM_INT_OP_JUMP_L] = "?L",
        [VM_INT_OP_BB_RLL] = "?bLL",
        [VM_INT_OP_RET_I] = "?I",
        [VM_INT_OP_RET_RV] = "?N",
        [VM_INT_OP_RET_RB] = "?b",
        [VM_INT_OP_RET_RI] = "?i",
        [VM_INT_OP_RET_RIF] = "?f",
        [VM_INT_OP_RET_RF] = "?l",
        [VM_INT_OP_RET_RA] = "?a",
        [VM_INT_OP_RET_RT] = "?t",
        [VM_INT_OP_CALL_T0] = "T:",
        [VM_INT_OP_CALL_T1] = "Td:",
        [VM_INT_OP_CALL_T2] = "Tdd:",
        [VM_INT_OP_CALL_T3] = "Tddd:",
        [VM_INT_OP_CALL_T4] = "Tdddd:",
        [VM_INT_OP_CALL_T5] = "Tddddd:",
        [VM_INT_OP_CALL_T6] = "Tdddddd:",
        [VM_INT_OP_CALL_T7] = "Tddddddd:",
        [VM_INT_OP_CALL_T8] = "Tdddddddd:",
        [VM_INT_OP_JUMP_T] = "?T",
        [VM_INT_OP_BB_RTT] = "?bTT",
        [VM_INT_OP_TAB] = ":",
        [VM_INT_OP_TSET_RRR] = "odd",
        [VM_INT_OP_TSET_RRF] = "odF",
        [VM_INT_OP_TSET_RFR] = "oFd",
        [VM_INT_OP_TSET_RFF] = "oFF",
        [VM_INT_OP_TGET_RR] = ":od",
        [VM_INT_OP_TGET_RF] = ":oF"};
    return table[opcode];
}

#endif
