/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** handle_value
*/

#include "../include/corewar.h"
#include <stdlib.h>

int handle_register(program_t *p, vm_t *vm, int *offset)
{
    unsigned int reg_num = vm->mem[p->pc + *offset];
    int value = 0;

    if (reg_num >= 1 && reg_num <= REG_NUMBER) {
        value = p->regs[reg_num];
    }
    *offset += 1;
    return value;
}

int handle_direct(program_t *p, vm_t *vm, int *offset)
{
    int value = *((int *)(vm->mem + p->pc + *offset));

    *offset += DIR_SIZE;
    return value;
}

int handle_indirect(program_t *p, vm_t *vm, int *offset, int mod_idx)
{
    unsigned short idx = *((unsigned short *)(vm->mem + p->pc + *offset));
    int value;

    if (mod_idx) {
        idx = idx % IDX_MOD;
    }
    value = *((int *)(vm->mem + (p->pc + idx) % MEM_SIZE));
    *offset += IND_SIZE;
    return value;
}
