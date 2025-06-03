/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** assembler_interpretator
*/

#include "../include/corewar.h"
#include <stdlib.h>

int fork_program(program_t *p, vm_t *vm)
{
    program_t *new_program;
    short offset;

    offset = *((short *)(vm->mem + p->pc + 1));
    new_program = (program_t *)malloc(sizeof(program_t));
    if (!new_program) {
        p->pc = (p->pc + 3) % MEM_SIZE;
        return 0;
    }
    *new_program = *p;
    new_program->pc = (p->pc + (offset % IDX_MOD)) % MEM_SIZE;
    new_program->next = NULL;
    add_program(vm, new_program);
    p->pc = (p->pc + 3) % MEM_SIZE;
    return 0;
}

static int lld_aux(vm_t *vm, unsigned int value, program_t *p, int *offset)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned int reg_num;

    if (((op_byte >> 4) & 0x3) == T_REG) {
        reg_num = vm->mem[p->pc + *offset];
        if (reg_num >= 1 && reg_num <= REG_NUMBER) {
            p->regs[reg_num] = value;
            p->regs[0] = (value == 0) ? 1 : 0;
        }
        *offset += 1;
    }
    return 0;
}

int lld(program_t *p, vm_t *vm)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned int value;
    int offset = 2;
    unsigned short idx;

    if (((op_byte >> 6) & 0x3) == T_DIR) {
        value = *((int *)(vm->mem + p->pc + offset));
        offset += DIR_SIZE;
    } else if (((op_byte >> 6) & 0x3) == T_IND) {
        idx = *((unsigned short *)(vm->mem + p->pc + offset));
        value = *((int *)(vm->mem + (p->pc + idx) % MEM_SIZE));
        offset += IND_SIZE;
    } else {
        p->pc = (p->pc + 1) % MEM_SIZE;
        return 0;
    }
    lld_aux(vm, value, p, &offset);
    p->pc = (p->pc + offset) % MEM_SIZE;
    return 0;
}

int lldi(program_t *p, vm_t *vm)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    int value1;
    int value2;
    int address;
    int reg_dest;
    int offset = 2;

    value1 = get_parameter_value_one(p, vm, &offset, 0);
    value2 = get_parameter_value_two(p, vm, &offset, 0);
    address = (p->pc + (value1 + value2)) % MEM_SIZE;
    if (((op_byte >> 2) & 0x3) == T_REG) {
        reg_dest = vm->mem[p->pc + offset];
        if (reg_dest >= 1 && reg_dest <= REG_NUMBER) {
            p->regs[reg_dest] = *((int *)(vm->mem + address));
            p->regs[0] = (p->regs[reg_dest] == 0) ? 1 : 0;
        }
        offset += 1;
    }
    p->pc = (p->pc + offset) % MEM_SIZE;
    return 0;
}

int lfork(program_t *p, vm_t *vm)
{
    program_t *new_program;
    short offset;

    offset = *((short *)(vm->mem + p->pc + 1));
    new_program = (program_t *)malloc(sizeof(program_t));
    if (!new_program) {
        p->pc = (p->pc + 3) % MEM_SIZE;
        return 0;
    }
    *new_program = *p;
    new_program->pc = (p->pc + offset) % MEM_SIZE;
    new_program->next = NULL;
    add_program(vm, new_program);
    p->pc = (p->pc + 3) % MEM_SIZE;
    return 0;
}

int aff(program_t *p, vm_t *vm)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned int reg_num;
    char value;
    int offset = 2;

    if (((op_byte >> 6) & 0x3) == T_REG) {
        reg_num = vm->mem[p->pc + offset];
        if (reg_num >= 1 && reg_num <= REG_NUMBER) {
            value = (char)(p->regs[reg_num] % 256);
            write(1, &value, 1);
        }
        offset += 1;
    }
    p->pc = (p->pc + offset) % MEM_SIZE;
    return 0;
}
