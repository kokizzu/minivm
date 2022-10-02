
#if !defined(VM_HEADER_OPCODE)
#define VM_HEADER_OPCODE

#include "lib.h"

enum {
    VM_OPCODE_EXIT,
    VM_OPCODE_REG,
    VM_OPCODE_JUMP,
    VM_OPCODE_FUNC,

    VM_OPCODE_CALL,
    VM_OPCODE_DCALL,
    VM_OPCODE_ADDR,
    VM_OPCODE_RET,

    VM_OPCODE_PUTCHAR,

    VM_OPCODE_INT,
    VM_OPCODE_NEG,
    VM_OPCODE_ADD,
    VM_OPCODE_SUB,
    VM_OPCODE_MUL,
    VM_OPCODE_DIV,
    VM_OPCODE_MOD,
    VM_OPCODE_BB,
    VM_OPCODE_BEQ,
    VM_OPCODE_BLT,

    VM_OPCODE_ARR,
    VM_OPCODE_SET,
    VM_OPCODE_GET,
    VM_OPCODE_LEN,

    VM_OPCODE_XCALL,
    VM_OPCODE_CCALL,

    VM_OPCODE_TYPE,
    VM_OPCODE_TAB,
    VM_OPCODE_NIL,
    VM_OPCODE_TRUE,
    VM_OPCODE_FALSE,
    
    VM_OPCODE_BOR,
    VM_OPCODE_BAND,
    VM_OPCODE_BXOR,
    VM_OPCODE_BSHL,
    VM_OPCODE_BSHR,
};

typedef uint32_t vm_opcode_t;

#endif
