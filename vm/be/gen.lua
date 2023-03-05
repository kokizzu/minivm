-- part: config
local VM_NREGS = 256
local VM_GOTO = true

local i = 1
while i < #arg do
    local val = arg[i]
    if val == '--goto=true' then
        VM_GOTO = true
    elseif val == '--goto=false' then
        VM_GOTO = false
    elseif val == '--goto' then
        i = i + 1
        if arg[i] == 'true' then
            VM_GOTO = true
        elseif arg[i] == 'false' then
            VM_GOTO = false
        elseif arg[i] == nil then
            error('--goto: expected true or false as an argument, not end of arguments')
        else
            error('--goto: bad argument ' .. arg[i])
        end
    elseif val == '--regs' then
        i = i + 1
        if arg[i] == 'nil' then
            error('--regs: expected argument, not end of arguments')
        elseif tonumber(arg[i]) == nil then
            error('--regs: bad number' .. arg[i])
        else
            VM_NREGS = tonumber(arg[i])
        end
    else
        error('unexpected arg: ' .. val)
    end
    i = i + 1
end

-- part: util

local typenametab = {
    i8 = 'int8_t',
    i16 = 'int16_t',
    i32 = 'int32_t',
    i64 = 'int64_t',
    u8 = 'uint8_t',
    u16 = 'uint16_t',
    u32 = 'uint32_t',
    u64 = 'uint64_t',
    f32 = 'float',
    f64 = 'double',
    func = 'vm_rblock_t *',
}

local function typename(name)
    return typenametab[name]
end

local function dump(name, data)
    local val = assert(io.open(name, "w"))
    val.write(val, data)
    val.close(val)
end

-- part: instrs

local prefix = 'VM_OPCODE'

local instrs = {}

local function push(op, ctype, args)
    if #args == 0 then
        args = {'void'}
    end
    local nametab = {prefix, op, ctype, table.concat(args, '_')}
    local dotab = {'do', op, ctype, table.concat(args, '_')}
    instrs[#instrs + 1] = {
        op = op,
        type = ctype,
        args = args,
        name = string.upper(table.concat(nametab, '_')),
        label = string.lower(table.concat(dotab, '_'))
    }
end

local function get_install_binary_branch(ctype)
    return function(op)
        local function install_math_const(lhs, rhs)
            push(op, ctype, {lhs, rhs, 'func', 'func'})
            push(op, ctype, {lhs, rhs, 'ptr', 'ptr'})
        end

        install_math_const('reg', 'reg')
        install_math_const('reg', 'const')
        install_math_const('const', 'reg')
        install_math_const('const', 'const')
    end
end

local function install_basic_branch(ctype)
    push('bb', ctype, {'reg', 'func', 'func'})
    push('bb', ctype, {'const', 'func', 'func'})
    push('bb', ctype, {'reg', 'ptr', 'ptr'})
    push('bb', ctype, {'const', 'ptr', 'ptr'})
    local install_branch_op = get_install_binary_branch(ctype)
    install_branch_op('beq')
    install_branch_op('blt')
    -- for k,v in pairs(typenametab) do
    --     push('bt', ctype, {'reg'})
    -- end
end

local function get_install_binary(ctype)
    return function(op)
        local function install_math_const(lhs, rhs)
            push(op, ctype, {lhs, rhs})
        end

        install_math_const('reg', 'reg')
        install_math_const('reg', 'const')
        install_math_const('const', 'reg')
        install_math_const('const', 'const')
    end
end

local function install_basic_math(ctype)
    local install_math_op = get_install_binary(ctype)
    install_math_op('add')
    install_math_op('sub')
    install_math_op('mul')
    install_math_op('div')
    install_math_op('mod')
end

local function install_basic_extra(ctype)
    push('move', ctype, {'reg'})
    push('move', ctype, {'const'})
    push('out', ctype, {'reg'})
    push('out', ctype, {'const'})
    push('in', ctype, {})
    push('ret', ctype, {'reg'})
    push('ret', ctype, {'const'})
end

local function install_basic(ctype)
    install_basic_math(ctype)
    install_basic_branch(ctype)
    install_basic_extra(ctype)
end

local function install_basic_and_bitwise(ctype)
    install_basic(ctype)
    local install_bitwise_op = get_install_binary(ctype)
    push('bnot', ctype, {'reg'})
    push('bnot', ctype, {'const'})
    install_bitwise_op('bor')
    install_bitwise_op('bxor')
    install_bitwise_op('band')
    install_bitwise_op('bshl')
    install_bitwise_op('bshr')
end

local function install_call(nargs)
    local function install_call_with(type)
        local regs = {type}
        for i = 1, nargs do
            regs[#regs + 1] = 'reg'
        end
        if type == 'const' then
            push('call', 'ptr', regs)
        end
        push('call', 'func', regs)
    end
    install_call_with('const')
    install_call_with('reg')
end

install_basic_and_bitwise('i8')
install_basic_and_bitwise('i16')
install_basic_and_bitwise('i32')
install_basic_and_bitwise('i64')
install_basic_and_bitwise('u8')
install_basic_and_bitwise('u16')
install_basic_and_bitwise('u32')
install_basic_and_bitwise('u64')

install_basic('f32')
install_basic('f64')

push('exit', 'break', {})
push('jump', 'ptr', {'const'})
push('jump', 'func', {'const'})

for i = 0, 8 do
    install_call(i)
end

-- part: emit header

do
    local lines = {}

    lines[#lines + 1] = [[
#if !defined(VM_HEADER_BE_INT3)
#define VM_HEADER_BE_INT3

#include <stdint.h>
#include "../ir.h"
]]

    lines[#lines + 1] = 'enum {'

    local cases = {}

    for key, instr in ipairs(instrs) do
        cases[#cases + 1] = '    ' .. instr.name .. ' = ' .. tostring(key)
    end

    lines[#lines + 1] = table.concat(cases, ',\n')

    lines[#lines + 1] = '};'
    lines[#lines + 1] = '#define VM_NREGS ' .. tostring(VM_NREGS)

    lines[#lines + 1] = [[
struct vm_state_t;
typedef struct vm_state_t vm_state_t;

union vm_opcode_t;
typedef union vm_opcode_t vm_opcode_t;

#include "./type.h"

union vm_opcode_t {
    size_t reg;
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    float f32;
    double f64;
    vm_rblock_t *func;
    void *ptr;
    vm_tag_t *ptag;
    size_t size;
};

struct vm_state_t {
    vm_opcode_t **ips;
    size_t framesize;
    size_t nlocals;
    void *locals;
]]
if VM_GOTO then
    lines[#lines + 1] = '    void **ptrs;'
end
lines[#lines + 1] = [[
};

void vm_run(vm_state_t *state, vm_block_t *block);


#endif
]]
    
if VM_GOTO then
    lines[#lines + 1] = '    #define VM_STATE_LOAD_PTR(state, num) ((state)->ptrs[(num)])'
    lines[#lines + 1] = '    #define VM_OPCODE_PTR ptr'
else
    lines[#lines + 1] = '    #define VM_STATE_LOAD_PTR(state, num) ((void) (state), (num))'
    lines[#lines + 1] = '    #define VM_OPCODE_PTR reg'
end
    
    local incheadersrc = table.concat(lines, '\n')

    dump('vm/be/int3.h', incheadersrc)
end

-- part: emit int3.c

do
    local lines = {}

    lines[#lines + 1] = '#include "./int3.h"'
    lines[#lines + 1] = '#include "./value.h"'
    lines[#lines + 1] = '#include "../tag.h"'

    local simplebinary = {
        add = '+',
        sub = '-',
        mul = '*',
        div = '/',
        bor = '|',
        bxor = '^',
        band = '&',
        bshl = '>>',
        bshr = '<<'
    }

    local simplebranch = {
        beq = '==',
        blt = '<'
    }

    local isinttype = {
        i8 = true,
        i16 = true,
        i32 = true,
        i64 = true,
        u8 = true,
        u16 = true,
        u32 = true,
        u64 = true,
        f32 = false,
        f64 = false
    }

    do
        local binaryint = {'add', 'sub', 'mul', 'div', 'mod', 'bor', 'bxor', 'band', 'bshl', 'bshr'}
        local binaryfloat = {'add', 'sub', 'mul', 'div', 'mod'}
        local binarytypes = {'i8', 'i16', 'i32', 'i64', 'u8', 'u16', 'u32', 'u64', 'f32', 'f64'}

        local map = {
            reg = '== VM_ARG_REG',
            const = '!= VM_ARG_REG'
        }

        local kinds = {{'reg', 'reg'}, {'reg', 'const'}, {'const', 'reg'}, {'const', 'const'}}

        lines[#lines + 1] = 'vm_opcode_t *vm_run_comp(vm_state_t *state, vm_rblock_t *rblock) {'
        lines[#lines + 1] = '    vm_opcode_t *ret = vm_cache_get(&rblock->block->cache, rblock);'
        lines[#lines + 1] = '    if (ret != NULL) {'
        lines[#lines + 1] = '        return ret;'
        lines[#lines + 1] = '    }'
        lines[#lines + 1] = '    vm_block_t *block = rblock->block;'
        lines[#lines + 1] = '    vm_tag_t *types = vm_rblock_regs_dup(rblock->regs);'
        lines[#lines + 1] = '    vm_rblock_t *rnext = vm_rblock_new(rblock->block, rblock->regs);'
        lines[#lines + 1] = '    rnext->start = rblock->start;'
        lines[#lines + 1] = '    size_t aops = 64;'
        lines[#lines + 1] = '    vm_opcode_t *ops = vm_malloc(sizeof(vm_opcode_t) * aops);'
        lines[#lines + 1] = '    size_t nops = 0;'
        lines[#lines + 1] = '    fprintf(stderr, "start = %zu\\n", rnext->start);'
        lines[#lines + 1] = '    for (size_t ninstr = rnext->start; ninstr < block->len; ninstr++) {'
        lines[#lines + 1] = '        if (nops + 16 + VM_TAG_MAX >= aops) {'
        lines[#lines + 1] = '            aops = (nops + 16) * 2;'
        lines[#lines + 1] = '            ops = vm_realloc(ops, sizeof(vm_opcode_t) * aops);'
        lines[#lines + 1] = '        }'
        lines[#lines + 1] = '        vm_instr_t instr = vm_rblock_type_specialize_instr(types, block->instrs[ninstr]);'
        lines[#lines + 1] = '        vm_print_instr(stderr, instr); fprintf(stderr, "\\n");'
        lines[#lines + 1] = '        switch (instr.op) {'
        do
            lines[#lines + 1] = '        case VM_IOP_MOVE: {'
            lines[#lines + 1] = '            if (instr.out.type == VM_ARG_NONE) {'
            lines[#lines + 1] = '                break;'
            lines[#lines + 1] = '            }'
            lines[#lines + 1] = '            if (vm_tag_eq(instr.tag, VM_TAG_NIL)) {'
            lines[#lines + 1] = '                break;'
            lines[#lines + 1] = '            }'
            do
                lines[#lines + 1] = '            if (instr.args[0].type == VM_ARG_STR) {'
                lines[#lines + 1] = '                if (vm_tag_eq(VM_TAG_I32, VM_TAG_PTR)) {'
                local name = string.upper(table.concat({prefix, 'move', 'u32', 'const'}, '_'))
                lines[#lines + 1] = '                    ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
                lines[#lines + 1] = '                    ops[nops++].u32 = (uint32_t) (size_t) instr.args[0].str;'
                lines[#lines + 1] = '                    ops[nops++].reg = instr.out.reg;'
                lines[#lines + 1] = '                } else {'
                local name = string.upper(table.concat({prefix, 'move', 'u64', 'const'}, '_'))
                lines[#lines + 1] = '                    ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
                lines[#lines + 1] = '                    ops[nops++].u64 = (uint64_t) (size_t) instr.args[0].str;'
                lines[#lines + 1] = '                    ops[nops++].reg = instr.out.reg;'
                lines[#lines + 1] = '                }'
                lines[#lines + 1] = '                break;'
                lines[#lines + 1] = '            }'
            end
            for tkey, tvalue in ipairs(binarytypes) do
                lines[#lines + 1] = '            if (vm_tag_eq(instr.tag, VM_TAG_' .. string.upper(tvalue) .. ')) {'
                for _, a0type in ipairs({'reg', 'const'}) do
                    lines[#lines + 1] = '                if (instr.args[0].type ' .. map[a0type] .. ') {'
                    local name = string.upper(table.concat({prefix, 'move', tvalue, a0type}, '_'))
                    lines[#lines + 1] = '                    ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
                    if a0type == 'reg' then
                        lines[#lines + 1] = '                    ops[nops++].reg = instr.args[0].reg;'
                    else
                        lines[#lines + 1] =
                            '                    ops[nops++].' .. tvalue .. ' = (' .. typename(tvalue) .. ') instr.args[0].num;'
                    end
                    lines[#lines + 1] = '                    ops[nops++].reg = instr.out.reg;'
                    lines[#lines + 1] = '                    break;'
                    lines[#lines + 1] = '                }'
                end
                lines[#lines + 1] = '            }'
            end
            lines[#lines + 1] = '            __builtin_trap();'
            lines[#lines + 1] = '        }'
        end
        do
            lines[#lines + 1] = '        case VM_IOP_BNOT: {'
            lines[#lines + 1] = '            if (instr.out.type == VM_ARG_NONE) {'
            lines[#lines + 1] = '                break;'
            lines[#lines + 1] = '            }'
            for tkey, tvalue in ipairs(binarytypes) do
                if isinttype[tvalue] then
                    lines[#lines + 1] = '            if (vm_tag_eq(instr.tag, VM_TAG_' .. string.upper(tvalue) .. ')) {'
                    for _, a0type in ipairs({'reg', 'const'}) do
                        lines[#lines + 1] = '                if (instr.args[0].type ' .. map[a0type] .. ') {'
                        local name = string.upper(table.concat({prefix, 'bnot', tvalue, a0type}, '_'))
                        lines[#lines + 1] = '                    ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
                        if a0type == 'reg' then
                            lines[#lines + 1] = '                    ops[nops++].reg = instr.args[0].reg;'
                        else
                            lines[#lines + 1] = '                    ops[nops++].' .. tvalue .. ' = (' .. typename(tvalue) .. ') instr.args[0].num;'
                        end
                        lines[#lines + 1] = '                    ops[nops++].reg = instr.out.reg;'
                        lines[#lines + 1] = '                    break;'
                        lines[#lines + 1] = '                }'
                    end
                    lines[#lines + 1] = '            }'
                end
            end
            lines[#lines + 1] = '            __builtin_trap();'
            lines[#lines + 1] = '        }'
        end
        for key, value in ipairs(binaryint) do
            lines[#lines + 1] = '        case VM_IOP_' .. string.upper(value) .. ': {'
            lines[#lines + 1] = '            if (instr.out.type == VM_ARG_NONE) {'
            lines[#lines + 1] = '                break;'
            lines[#lines + 1] = '            }'
            for tkey, tvalue in ipairs(binarytypes) do
                if isinttype[tvalue] or value == 'add' or value == 'sub' or value == 'mul' or value == 'div' or value ==
                    'mod' then
                    lines[#lines + 1] = '            if (vm_tag_eq(instr.tag, VM_TAG_' .. string.upper(tvalue) .. ')) {'
                    for _, pair in ipairs(kinds) do
                        lines[#lines + 1] = '                if (instr.args[0].type ' .. map[pair[1]] .. ' && ' .. 'instr.args[1].type ' .. map[pair[2]] .. ') {'
                        local name = string.upper(table.concat({prefix, value, tvalue, pair[1], pair[2]}, '_'))
                        lines[#lines + 1] = '                    ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
                        if pair[1] == 'reg' then
                            lines[#lines + 1] = '                    ops[nops++].reg = instr.args[0].reg;'
                        else
                            lines[#lines + 1] = '                    ops[nops++].' .. tvalue .. ' = (' .. typename(tvalue) .. ') instr.args[0].num;'
                        end
                        if pair[2] == 'reg' then
                            lines[#lines + 1] = '                    ops[nops++].reg = instr.args[1].reg;'
                        else
                            lines[#lines + 1] = '                    ops[nops++].' .. tvalue .. ' = (' .. typename(tvalue) .. ') instr.args[1].num;'
                        end
                        lines[#lines + 1] = '                    ops[nops++].reg = instr.out.reg;'
                        lines[#lines + 1] = '                    break;'
                        lines[#lines + 1] = '                }'
                    end
                    lines[#lines + 1] = '            }'
                end
            end
            lines[#lines + 1] = '            __builtin_trap();'
            lines[#lines + 1] = '        }'
        end
        do
            lines[#lines + 1] = '        case VM_IOP_IN: {'
            lines[#lines + 1] = '            if (instr.out.type == VM_ARG_NONE) {'
            lines[#lines + 1] = '                break;'
            lines[#lines + 1] = '            }'
            for tkey, tvalue in ipairs(binarytypes) do
                lines[#lines + 1] = '            if (vm_tag_eq(instr.tag, VM_TAG_' .. string.upper(tvalue) .. ')) {'
                local name = string.upper(table.concat({prefix, 'in', tvalue, 'void'}, '_'))
                lines[#lines + 1] = '                    ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
                lines[#lines + 1] = '                    ops[nops++].reg = instr.args[0].reg;'
                lines[#lines + 1] = '            }'
            end
            lines[#lines + 1] = '            break;'
            lines[#lines + 1] = '        }'
        end
        do
            lines[#lines + 1] = '        case VM_IOP_CALL: {'
            for nargs = 0, 8 do
                lines[#lines + 1] = '            if (instr.args[' .. tostring(nargs + 1) .. '].type == VM_ARG_NONE) {'
                for _, val in ipairs({'const', 'reg'}) do
                    if val == 'const' then
                        lines[#lines + 1] = '                if (instr.args[0].type == VM_ARG_FUNC) {'
                    else
                        lines[#lines + 1] = '                else if (instr.args[0].type == VM_ARG_REG) {'
                    end
                    local name = {prefix, 'call', 'func', val}
                    for i=1, nargs do
                        name[#name + 1] = 'reg'
                    end
                    name = string.upper(table.concat(name, '_'))
                    lines[#lines + 1] = '                    ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
                    if val == 'reg' then
                        lines[#lines + 1] = '                    ops[nops++].reg = instr.args[0].reg;'
                    else
                        lines[#lines + 1] = '                    vm_tag_t *args = vm_rblock_regs_empty();'
                        for argno = 1, nargs do
                            lines[#lines + 1] = '                    args[' .. tostring(argno) .. '] = types[instr.args[' .. tostring(argno) .. '].reg];'
                        end
                        lines[#lines + 1] = '                    ops[nops++].func = vm_rblock_new(instr.args[0].func, args);'
                    end
                    for argno = 1, nargs do
                        lines[#lines + 1] = '                    ops[nops++].reg = instr.args[' .. tostring(argno) .. '].reg;'
                    end
                    lines[#lines + 1] = '                    if (instr.out.type == VM_ARG_NONE) {'
                    lines[#lines + 1] = '                        ops[nops++].reg = VM_NREGS;'
                    lines[#lines + 1] = '                    } else {'
                    lines[#lines + 1] = '                        ops[nops++].reg = instr.out.reg;'
                    lines[#lines + 1] = '                    }'
                    lines[#lines + 1] = '                    for (vm_tag_t type = 0; type < VM_TAG_MAX; type++) {'
                    lines[#lines + 1] = '                        vm_tag_t *types_tag = vm_rblock_regs_dup(types);'
                    lines[#lines + 1] = '                        if (instr.out.type == VM_ARG_REG) {'
                    lines[#lines + 1] = '                            types_tag[instr.out.reg] = type;'
                    lines[#lines + 1] = '                        }'
                    lines[#lines + 1] = '                        vm_rblock_t *rest_block = vm_rblock_new(rnext->block, types_tag);'
                    lines[#lines + 1] = '                        rest_block->start = ninstr+1;'
                    lines[#lines + 1] = '                        ops[nops++].size = ((size_t) rest_block) + 1;'
                    lines[#lines + 1] = '                    }'
                    lines[#lines + 1] = '                    goto early_return;'
                    lines[#lines + 1] = '                }'
                end
                lines[#lines + 1] = '            }'
            end
            lines[#lines + 1] = '            __builtin_trap();'
            lines[#lines + 1] = '        }'
        end
        do
            lines[#lines + 1] = '        case VM_IOP_OUT: {'
            for tkey, tvalue in ipairs(binarytypes) do
                lines[#lines + 1] = '            if (vm_tag_eq(instr.tag, VM_TAG_' .. string.upper(tvalue) .. ')) {'
                for _, val in ipairs({'const', 'reg'}) do
                    local name = string.upper(table.concat({prefix, 'out', tvalue, val}, '_'))
                    lines[#lines + 1] = '                if (instr.args[0].type ' .. map[val] .. ') {'
                    lines[#lines + 1] = '                    ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
                    if val == 'reg' then
                        lines[#lines + 1] = '                    ops[nops++].reg = instr.args[0].reg;'
                    else
                        lines[#lines + 1] =
                            '                    ops[nops++].' .. tvalue .. ' = (' .. typename(tvalue) .. ') instr.args[0].num;'
                    end
                    lines[#lines + 1] = '                    break;'
                    lines[#lines + 1] = '                }'
                end
                lines[#lines + 1] = '            }'
            end
            lines[#lines + 1] = '        }'
            lines[#lines + 1] = '        default: __builtin_trap();'
        end
        lines[#lines + 1] = '        }'
        lines[#lines + 1] = '        if (instr.out.type == VM_ARG_REG) {'
        lines[#lines + 1] = '            types[instr.out.reg] = instr.tag;'
        lines[#lines + 1] = '        }'
        lines[#lines + 1] = '    }'
        lines[#lines + 1] = '    vm_branch_t branch = vm_rblock_type_specialize_branch(types, block->branch);'
        lines[#lines + 1] = '    switch (branch.op) {'
        do
            lines[#lines + 1] = '        case VM_BOP_EXIT: {'
            local name = string.upper(table.concat({prefix, 'exit', 'break', 'void'}, '_'))
            if VM_GOTO then
                lines[#lines + 1] = '                    ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
            else
                lines[#lines + 1] = '                    ops[nops++].reg = ' .. name .. ';'
            end
            lines[#lines + 1] = '            break;'
            lines[#lines + 1] = '        }'
        end
        do
            lines[#lines + 1] = '        case VM_BOP_JUMP: {'
            local name = string.upper(table.concat({prefix, 'jump', 'func', 'const'}, '_'))
            if VM_GOTO then
                lines[#lines + 1] = '            ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
            else
                lines[#lines + 1] = '            ops[nops++].reg = ' .. name .. ';'
            end
            lines[#lines + 1] = '            ops[nops++].func = vm_rblock_new(branch.targets[0], types);'
            lines[#lines + 1] = '            break;'
            lines[#lines + 1] = '        }'
        end
        do
            lines[#lines + 1] = '        case VM_BOP_BTYPE: {'
            local name = string.upper(table.concat({prefix, 'jump', 'func', 'const'}, '_'))
            if VM_GOTO then
                lines[#lines + 1] = '            ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
            else
                lines[#lines + 1] = '            ops[nops++].reg = ' .. name .. ';'
            end
            lines[#lines + 1] = '            if (vm_tag_eq(branch.tag, types[branch.args[0].reg])) {'
            lines[#lines + 1] = '                ops[nops++].func = vm_rblock_new(branch.targets[0], types);'
            lines[#lines + 1] = '            } else {'
            lines[#lines + 1] = '                ops[nops++].func = vm_rblock_new(branch.targets[1], types);'
            lines[#lines + 1] = '            }'
            lines[#lines + 1] = '            break;'
            lines[#lines + 1] = '        }'
        end
        do
            lines[#lines + 1] = '        case VM_BOP_RET: {'
            for tkey, tvalue in ipairs(binarytypes) do
                lines[#lines + 1] = '            if (vm_tag_eq(branch.tag, VM_TAG_' .. string.upper(tvalue) .. ')) {'
                for _, val in ipairs({'const', 'reg'}) do
                    lines[#lines + 1] = '                if (branch.args[0].type ' .. map[val] .. ') {'
                    local name = string.upper(table.concat({prefix, 'ret', tvalue, val}, '_'))
                    lines[#lines + 1] = '                    ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
                    if val == 'reg' then
                        lines[#lines + 1] = '                    ops[nops++].reg = branch.args[0].reg;'
                    else
                        lines[#lines + 1] = '                    ops[nops++].' .. tvalue .. ' = (' .. typename(tvalue) .. ') branch.args[0].num;'
                    end
                    lines[#lines + 1] = '                    break;'
                    lines[#lines + 1] = '                }'
                end
                lines[#lines + 1] = '            }'
            end
            lines[#lines + 1] = '            __builtin_trap();'
            lines[#lines + 1] = '        }'
        end
        do
            lines[#lines + 1] = '        case VM_BOP_BB: {'
            for tkey, tvalue in ipairs(binarytypes) do
                lines[#lines + 1] = '                if (vm_tag_eq(branch.tag, VM_TAG_' .. string.upper(tvalue) .. ')) {'
                for _, val in ipairs({'const', 'reg'}) do
                    lines[#lines + 1] = '                    if (branch.args[0].type ' .. map[val] .. ') {'
                    local name = string.upper(table.concat({prefix, 'bb', tvalue, val, 'func', 'func'}, '_'))
                    lines[#lines + 1] = '                    ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
                    if val == 'reg' then
                        lines[#lines + 1] = '                    ops[nops++].reg = branch.args[0].reg;'
                    else
                        lines[#lines + 1] =
                            '                    ops[nops++].' .. tvalue .. ' = (' .. typename(tvalue) .. ') branch.args[0].num;'
                    end
                    lines[#lines + 1] = '                    ops[nops++].func = vm_rblock_new(branch.targets[0], types);'
                    lines[#lines + 1] = '                    ops[nops++].func = vm_rblock_new(branch.targets[1], types);'
                    lines[#lines + 1] = '                    break;'
                    lines[#lines + 1] = '                    }'
                end
                lines[#lines + 1] = '                    break;'
                lines[#lines + 1] = '                }'
            end
            lines[#lines + 1] = '             __builtin_trap();'
            lines[#lines + 1] = '        }'
        end
        do
            for key, value in ipairs({'blt', 'beq'}) do
                lines[#lines + 1] = '        case VM_BOP_' .. string.upper(value) .. ': {'
                for tkey, tvalue in ipairs(binarytypes) do
                    lines[#lines + 1] = '            if (vm_tag_eq(branch.tag, VM_TAG_' .. string.upper(tvalue) .. ')) {'
                    for _, pair in ipairs(kinds) do
                        lines[#lines + 1] =
                            '                if (branch.args[0].type ' .. map[pair[1]] .. ' && ' .. 'branch.args[1].type ' .. map[pair[2]] .. ') {'
                        local name = string.upper(table.concat(
                            {prefix, value, tvalue, pair[1], pair[2], 'func', 'func'}, '_'))
                        lines[#lines + 1] = '                    ops[nops++].VM_OPCODE_PTR = VM_STATE_LOAD_PTR(state, ' .. name .. ');'
                        if pair[1] == 'reg' then
                            lines[#lines + 1] = '                    ops[nops++].reg = branch.args[0].reg;'
                        else
                            lines[#lines + 1] = '                    ops[nops++].' .. tvalue .. ' = (' .. typename(tvalue) .. ') branch.args[0].num;'
                        end
                        if pair[2] == 'reg' then
                            lines[#lines + 1] = '                    ops[nops++].reg = branch.args[1].reg;'
                        else
                            lines[#lines + 1] = '                    ops[nops++].' .. tvalue .. ' = (' .. typename(tvalue) .. ') branch.args[1].num;'
                        end
                        lines[#lines + 1] = '                    ops[nops++].func = vm_rblock_new(branch.targets[0], types);'
                        lines[#lines + 1] = '                    ops[nops++].func = vm_rblock_new(branch.targets[1], types);'
                        lines[#lines + 1] = '                    break;'
                        lines[#lines + 1] = '                }'
                    end
                    lines[#lines + 1] = '            }'
                end
                lines[#lines + 1] = '             __builtin_trap();'
                lines[#lines + 1] = '        }'
            end
        end
        do
            lines[#lines + 1] = '        default: __builtin_trap();'
        end
        lines[#lines + 1] = '    }'
        lines[#lines + 1] = 'early_return:;'
        lines[#lines + 1] = '    vm_cache_set(&rblock->block->cache, rnext, ops);'
        lines[#lines + 1] = '    return ops;'
        lines[#lines + 1] = '}'
    
        local incheadersrc = table.concat(lines, '\n')

        dump('vm/be/comp.c', incheadersrc)
    end

    local lines = {}

    lines[#lines + 1] = '#include "./int3.h"'
    lines[#lines + 1] = '#include "./value.h"'
    lines[#lines + 1] = '#include "../tag.h"'

    lines[#lines + 1] = 'void vm_run(vm_state_t *state, vm_block_t *block) {'

    if VM_GOTO then
        local cases = {}

        lines[#lines + 1] = '    void *ptrs[] = {'
        for key, instr in ipairs(instrs) do
            cases[#cases + 1] = '        [' .. instr.name .. '] = &&' .. instr.label
        end

        lines[#lines + 1] = table.concat(cases, ',\n')
        lines[#lines + 1] = '    };'

        lines[#lines + 1] = '    state->ptrs = ptrs;'
    end
    lines[#lines + 1] = '    vm_opcode_t *restrict ip = vm_run_comp(state, vm_rblock_new(block, vm_rblock_regs_empty()));'
    lines[#lines + 1] = '    vm_value_t *restrict locals = state->locals;'
    lines[#lines + 1] = '    vm_opcode_t **restrict ips = state->ips;'
    if VM_GOTO then
        lines[#lines + 1] = '    goto *(ip++)->ptr;'
    else
        lines[#lines + 1] = '    redo:; switch ((ip++)->reg) {'
    end

    do
        local cases = {}

        for key, instr in ipairs(instrs) do
            local case = {}

            if VM_GOTO then
                case[#case + 1] = '    ' .. instr.label .. ': {'
            else
                case[#case + 1] = '    case ' .. instr.name .. ': {'
            end
            -- case[#case+1] = '        printf("' .. instr.name .. '\\n");'
            -- case[#case+1] = '        fflush(stderr);'

            if simplebinary[instr.op] then
                local tname = typename(instr.type)
                if instr.args[1] == 'reg' then
                    case[#case + 1] = '        ' .. tname .. ' a0 = locals[(ip++)->reg].' .. instr.type .. ';'
                else
                    case[#case + 1] = '        ' .. tname .. ' a0 = (ip++)->' .. instr.type .. ';'
                end
                if instr.args[2] == 'reg' then
                    case[#case + 1] = '        ' .. tname .. ' a1 = locals[(ip++)->reg].' .. instr.type .. ';'
                else
                    case[#case + 1] = '        ' .. tname .. ' a1 = (ip++)->' .. instr.type .. ';'
                end
                -- case[#case+1] = '        printf("%zi ' ..simplebinary[instr.op] .. ' %zi\\n", (ptrdiff_t) a0, (ptrdiff_t) a1);'
                case[#case + 1] = '        locals[(ip++)->reg].' .. instr.type .. ' = a0 ' .. simplebinary[instr.op] .. ' a1;'
            elseif instr.op == 'mod' then
                local tname = typename(instr.type)
                if instr.args[1] == 'reg' then
                    case[#case + 1] = '        ' .. tname .. ' a0 = locals[(ip++)->reg].' .. instr.type .. ';'
                else
                    case[#case + 1] = '        ' .. tname .. ' a0 = (ip++)->' .. instr.type .. ';'
                end
                if instr.args[2] == 'reg' then
                    case[#case + 1] = '        ' .. tname .. ' a1 = locals[(ip++)->reg].' .. instr.type .. ';'
                else
                    case[#case + 1] = '        ' .. tname .. ' a1 = (ip++)->' .. instr.type .. ';'
                end
                if instr.type == 'f64' then
                    case[#case + 1] = '        locals[(ip++)->reg].' .. instr.type .. ' = fmod(a0, a1);'
                elseif instr.type == 'f32' then
                    case[#case + 1] = '        locals[(ip++)->reg].' .. instr.type .. ' = fmodf(a0, a1);'
                else
                    case[#case + 1] = '        locals[(ip++)->reg].' .. instr.type .. ' = a0 % a1;'
                end
            elseif instr.op == 'move' then
                local tname = typename(instr.type)
                if instr.args[1] == 'reg' then
                    case[#case + 1] = '        ' .. tname .. ' a0 = locals[(ip++)->reg].' .. instr.type .. ';'
                else
                    case[#case + 1] = '        ' .. tname .. ' a0 = (ip++)->' .. instr.type .. ';'
                end
                case[#case + 1] = '        locals[(ip++)->reg].' .. instr.type .. ' = a0;'
            elseif instr.op == 'bnot' then
                local tname = typename(instr.type)
                if instr.args[1] == 'reg' then
                    case[#case + 1] = '        ' .. tname .. ' a0 = locals[(ip++)->reg].' .. instr.type .. ';'
                else
                    case[#case + 1] = '        ' .. tname .. ' a0 = (ip++)->' .. instr.type .. ';'
                end
                case[#case + 1] = '        locals[(ip++)->reg].' .. instr.type .. ' = ~a0;'
            elseif instr.op == 'in' then
                local tname = typename(instr.type)
                case[#case + 1] = '        locals[(ip++)->reg].' .. instr.type .. ' = (' .. tname .. ') fgetc(stdin);'
            elseif instr.op == 'out' then
                local tname = typename(instr.type)
                if instr.args[1] == 'reg' then
                    case[#case + 1] = '        ' .. tname .. ' a0 = locals[(ip++)->reg].' .. instr.type .. ';'
                else
                    case[#case + 1] = '        ' .. tname .. ' a0 = (ip++)->' .. instr.type .. ';'
                end
                case[#case + 1] = '        putchar((int) a0);'
            elseif instr.op == 'jump' and instr.type == 'ptr' then
                case[#case + 1] = '            ip = ip[0].ptr;'
            elseif instr.op == 'jump' and instr.type == 'func' then
                case[#case + 1] = '        vm_opcode_t *head = ip-1;'
                if VM_GOTO then
                    case[#case + 1] = '        head->ptr = &&' .. table.concat({'do', instr.op, 'ptr', 'const'}, '_') .. ';'
                else
                    case[#case + 1] = '        head->reg = ' .. string.upper(table.concat({prefix, instr.op, 'ptr', 'const'}, '_')) .. ';'
                end
                case[#case + 1] = '        ip[0].ptr = vm_run_comp(state, ip[0].func);'
                case[#case + 1] = '        ip = head;'
            elseif instr.op == 'bb' and instr.args[2] == 'ptr' then
                local tname = typename(instr.type)
                if instr.args[1] == 'reg' then
                    case[#case + 1] = '        ' .. tname .. ' a0 = locals[ip[0].reg].' .. instr.type .. ';'
                else
                    case[#case + 1] = '        ' .. tname .. ' a0 = ip[0].' .. instr.type .. ';'
                end
                case[#case + 1] = '        if (a0 != 0) {'
                case[#case + 1] = '            ip = ip[1].ptr;'
                case[#case + 1] = '        } else {'
                case[#case + 1] = '            ip = ip[2].ptr;'
                case[#case + 1] = '        }'
            elseif instr.op == 'bb' and instr.args[2] == 'func' then
                case[#case + 1] = '        vm_opcode_t *head = ip-1;'
                if VM_GOTO then
                    case[#case + 1] = '        head->ptr = &&' .. table.concat({'do', instr.op, instr.type, instr.args[1], 'ptr', 'ptr'}, '_') .. ';'
                else
                    case[#case + 1] = '        head->reg = ' .. string.upper(table.concat({prefix, instr.op, instr.type, instr.args[1], 'ptr', 'ptr'}, '_')).. ';'
                end
                case[#case + 1] = '        ip[1].ptr = vm_run_comp(state, ip[1].func);'
                case[#case + 1] = '        ip = head;'
            elseif (instr.op == 'blt' or instr.op == 'beq') and instr.args[3] == 'ptr' then
                local tname = typename(instr.type)
                if instr.args[1] == 'reg' then
                    case[#case + 1] = '        ' .. tname .. ' a0 = locals[ip[0].reg].' .. instr.type .. ';'
                else
                    case[#case + 1] = '        ' .. tname .. ' a0 = ip[0].' .. instr.type .. ';'
                end
                if instr.args[0] == 'reg' then
                    case[#case + 1] = '        ' .. tname .. ' a1 = locals[ip[1].reg].' .. instr.type .. ';'
                else
                    case[#case + 1] = '        ' .. tname .. ' a1 = ip[1].' .. instr.type .. ';'
                end
                case[#case + 1] = '        if (a0 ' .. simplebranch[instr.op] .. ' a1) {'
                case[#case + 1] = '            ip = ip[2].ptr;'
                case[#case + 1] = '        } else {'
                case[#case + 1] = '            ip = ip[3].ptr;'
                case[#case + 1] = '        }'
            elseif (instr.op == 'blt' or instr.op == 'beq') and instr.args[3] == 'func' then
                case[#case + 1] = '        vm_opcode_t *head = ip-1;'
                if VM_GOTO then
                    case[#case + 1] = '        head->ptr = &&' .. table.concat({'do', instr.op, instr.type, instr.args[1], instr.args[2], 'ptr', 'ptr'}, '_') .. ';'
                else
                    case[#case + 1] = '        head->reg = ' .. string.upper(table.concat({prefix, instr.op, instr.type, instr.args[1], instr.args[2], 'ptr', 'ptr'}, '_')) .. ';'
                end
                case[#case + 1] = '        ip[2].ptr = vm_run_comp(state, ip[2].func);'
                case[#case + 1] = '        ip[3].ptr = vm_run_comp(state, ip[3].func);'
                case[#case + 1] = '        ip = head;'
            elseif instr.op == 'ret' then
                local tname = typename(instr.type)
                if instr.args[1] == 'reg' then
                    case[#case + 1] = '        ' .. tname .. ' a0 = locals[(ip++)->reg].' .. instr.type .. ';'
                else
                    case[#case + 1] = '        ' .. tname .. ' a0 = (ip++)->' .. instr.type .. ';'
                end
                case[#case + 1] = '        locals -= VM_NREGS;'
                case[#case + 1] = '        ip = *(ips--);'
                case[#case + 1] = '        locals[(ip++)->reg].' .. instr.type .. ' = (' .. tname .. ') a0;'
                case[#case + 1] = '        size_t addr = ip[VM_TAG_'..string.upper(instr.type)..'].size;'
                case[#case + 1] = '        if ((addr % 2) == 0) {'
                case[#case + 1] = '            ip = (vm_opcode_t *) addr;'
                case[#case + 1] = '        } else {'
                case[#case + 1] = '            addr -= 1;'
                case[#case + 1] = '            fprintf(stderr, "my start = %zu\\n", ((vm_rblock_t *)addr)->start);'
                case[#case + 1] = '            vm_opcode_t *ops = vm_run_comp(state, (vm_rblock_t *)addr);'
                case[#case + 1] = '            ip[VM_TAG_'..string.upper(instr.type)..'].size = (size_t) ops;'
                case[#case + 1] = '            ip = ops;'
                case[#case + 1] = '        }'
            elseif instr.op == 'call' and instr.args[1] == 'reg' then
                case[#case + 1] = '        vm_rblock_t *t0 = (ip++)->func;'
                for argno = 1, #instr.args - 1 do
                    case[#case + 1] = '        locals[' .. tostring(argno + VM_NREGS) .. '] = locals[(ip++)->reg];'
                end
                case[#case + 1] = '        locals += VM_NREGS;'
                case[#case + 1] = '        *(++ips) = ip;'
                case[#case + 1] = '        ip = vm_run_comp(state, t0);'
            elseif instr.op == 'call' and instr.type == 'ptr' then
                case[#case + 1] = '        vm_opcode_t *t0 = (ip++)->ptr;'
                for argno = 1, #instr.args - 1 do
                    case[#case + 1] = '        locals[' .. tostring(argno + VM_NREGS) .. '] = locals[(ip++)->reg];'
                end
                case[#case + 1] = '        locals += VM_NREGS;'
                case[#case + 1] = '        *(++ips) = ip;'
                case[#case + 1] = '        ip = t0;'
            elseif instr.op == 'call' and instr.type == 'func' then
                case[#case + 1] = '        vm_opcode_t *head = ip-1;'
                if VM_GOTO then
                    local argvs = {'do', instr.op, 'ptr'}
                    for argno = 1, #instr.args do
                        argvs[#argvs + 1] = instr.args[argno]
                    end
                    case[#case + 1] = '        head->ptr = &&' .. table.concat(argvs, '_') .. ';'
                else
                    local argvs = {prefix, instr.op, 'ptr'}
                    for argno = 1, #instr.args do
                        argvs[#argvs + 1] = instr.args[argno]
                    end
                    case[#case + 1] = '        head->reg = ' .. string.upper(table.concat(argvs, '_')) .. ';'
                end
                case[#case + 1] = '        ip[0].ptr = vm_run_comp(state, ip[0].func);'
                case[#case + 1] = '        ip = head;'
            elseif instr.op == 'exit' then
                case[#case + 1] = '        {return;}'
            else
                case[#case + 1] = '        fprintf(stderr, "unimplemend label: ' .. instr.name .. '\\n");'
                lines[#lines + 1] = '        exit(1);'
            end

            if VM_GOTO then
                case[#case + 1] = '        goto *(ip++)->ptr;'
            else
                case[#case + 1] = '        goto redo;'
            end
            case[#case + 1] = '    }'

            cases[#cases + 1] = table.concat(case, '\n')
        end

        lines[#lines + 1] = table.concat(cases, '\n')
    end

    if not VM_GOTO then
        lines[#lines + 1] = '    }'
    end
    lines[#lines + 1] = '}'

    local incheadersrc = table.concat(lines, '\n')

    dump('vm/be/int3.c', incheadersrc)
end
