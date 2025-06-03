/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** instructions_arithmetic
*/

#include "../include/corewar.h"
#include "../include/my.h"

static int validate_op_byte(unsigned char op_byte, program_t *p)
{
    if ((((op_byte >> 6) & 0x3) != T_REG) ||
        (((op_byte >> 4) & 0x3) != T_REG) ||
        (((op_byte >> 2) & 0x3) != T_REG)) {
        p->pc = (p->pc + 1) % MEM_SIZE;
        return 0;
    }
    return 1;
}

static int validate_registers(unsigned int reg1, unsigned int reg2,
    unsigned int reg3, program_t *p)
{
    int offset = 5;

    if (reg1 < 1 || reg1 > REG_NUMBER ||
        reg2 < 1 || reg2 > REG_NUMBER ||
        reg3 < 1 || reg3 > REG_NUMBER) {
        p->pc = (p->pc + offset) % MEM_SIZE;
        return 0;
    }
    return 1;
}

int add(program_t *p, vm_t *vm)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned int reg1;
    unsigned int reg2;
    unsigned int reg3;
    int offset = 2;

    if (!validate_op_byte(op_byte, p))
        return 0;
    reg1 = vm->mem[p->pc + offset];
    ++offset;
    reg2 = vm->mem[p->pc + offset];
    ++offset;
    reg3 = vm->mem[p->pc + offset];
    ++offset;
    if (!validate_registers(reg1, reg2, reg3, p))
        return 0;
    p->regs[reg3] = p->regs[reg1] + p->regs[reg2];
    p->regs[0] = (p->regs[reg3] == 0) ? 1 : 0;
    p->pc = (p->pc + offset) % MEM_SIZE;
    return 0;
}

int validate_sub_operation(program_t *p, vm_t *vm, unsigned char op_byte,
    int offset)
{
    unsigned int reg1 = vm->mem[p->pc + offset];
    unsigned int reg2 = vm->mem[p->pc + offset + 1];
    unsigned int reg3 = vm->mem[p->pc + offset + 2];

    if ((((op_byte >> 6) & 0x3) != T_REG) ||
        (((op_byte >> 4) & 0x3) != T_REG) ||
        (((op_byte >> 2) & 0x3) != T_REG)) {
        p->pc = (p->pc + 1) % MEM_SIZE;
        return 0;
    }
    if (reg1 < 1 || reg1 > REG_NUMBER ||
        reg2 < 1 || reg2 > REG_NUMBER ||
        reg3 < 1 || reg3 > REG_NUMBER) {
        p->pc = (p->pc + offset + 3) % MEM_SIZE;
        return 0;
    }
    return 1;
}

int sub(program_t *p, vm_t *vm)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned int reg1;
    unsigned int reg2;
    unsigned int reg3;
    int offset = 2;

    if (!validate_sub_operation(p, vm, op_byte, offset)) {
        return 0;
    }
    reg1 = vm->mem[p->pc + offset];
    ++offset;
    reg2 = vm->mem[p->pc + offset];
    ++offset;
    reg3 = vm->mem[p->pc + offset];
    ++offset;
    p->regs[reg3] = p->regs[reg1] - p->regs[reg2];
    p->regs[0] = (p->regs[reg3] == 0) ? 1 : 0;
    p->pc = (p->pc + offset) % MEM_SIZE;
    return 0;
}
