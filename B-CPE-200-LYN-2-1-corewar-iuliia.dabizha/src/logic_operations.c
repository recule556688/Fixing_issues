/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** assembler_interpretator
*/

#include "../include/corewar.h"

static int fetch_indirect_value(vm_t *vm, program_t *p, int *offset)
{
    unsigned short idx;
    int value;

    idx = *((unsigned short *)(vm->mem + p->pc + *offset));
    idx = idx % IDX_MOD;
    value = *((int *)(vm->mem + (p->pc + idx) % MEM_SIZE));
    *offset += IND_SIZE;
    return value;
}

static int get_parameter_value(program_t *p, vm_t *vm, unsigned char type,
    int *offset)
{
    int value = 0;
    unsigned int reg_num;

    if (type == T_REG) {
        reg_num = vm->mem[p->pc + *offset];
        if (reg_num >= 1 && reg_num <= REG_NUMBER) {
            value = p->regs[reg_num];
        }
        *offset += 1;
        return value;
    }
    if (type == T_DIR) {
        value = *((int *)(vm->mem + p->pc + *offset));
        *offset += DIR_SIZE;
        return value;
    }
    if (type == T_IND) {
        return fetch_indirect_value(vm, p, offset);
    }
    return value;
}

int and_f(program_t *p, vm_t *vm)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned int value1;
    unsigned int value2;
    unsigned int reg_dest;
    int offset = 2;

    value1 = get_parameter_value(p, vm, ((op_byte >> 6) & 0x3), &offset);
    value2 = get_parameter_value(p, vm, ((op_byte >> 4) & 0x3), &offset);
    if (((op_byte >> 2) & 0x3) == T_REG) {
        reg_dest = vm->mem[p->pc + offset];
        if (reg_dest >= 1 && reg_dest <= REG_NUMBER) {
            p->regs[reg_dest] = value1 & value2;
            p->regs[0] = (p->regs[reg_dest] == 0) ? 1 : 0;
        }
        offset += 1;
    }
    p->pc = (p->pc + offset) % MEM_SIZE;
    return 0;
}

int or_f(program_t *p, vm_t *vm)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned int value1;
    unsigned int value2;
    unsigned int reg_dest;
    int offset = 2;

    value1 = get_parameter_value(p, vm, ((op_byte >> 6) & 0x3), &offset);
    value2 = get_parameter_value(p, vm, ((op_byte >> 4) & 0x3), &offset);
    if (((op_byte >> 2) & 0x3) == T_REG) {
        reg_dest = vm->mem[p->pc + offset];
        if (reg_dest >= 1 && reg_dest <= REG_NUMBER) {
            p->regs[reg_dest] = value1 | value2;
            p->regs[0] = (p->regs[reg_dest] == 0) ? 1 : 0;
        }
        offset += 1;
    }
    p->pc = (p->pc + offset) % MEM_SIZE;
    return 0;
}

int xor_f(program_t *p, vm_t *vm)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned int value1;
    unsigned int value2;
    unsigned int reg_dest;
    int offset = 2;

    value1 = get_parameter_value(p, vm, ((op_byte >> 6) & 0x3), &offset);
    value2 = get_parameter_value(p, vm, ((op_byte >> 4) & 0x3), &offset);
    if (((op_byte >> 2) & 0x3) == T_REG) {
        reg_dest = vm->mem[p->pc + offset];
        if (reg_dest >= 1 && reg_dest <= REG_NUMBER) {
            p->regs[reg_dest] = value1 ^ value2;
            p->regs[0] = (p->regs[reg_dest] == 0) ? 1 : 0;
        }
        offset += 1;
    }
    p->pc = (p->pc + offset) % MEM_SIZE;
    return 0;
}
