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
    int value = 0;
    int i;

    // Read 4 bytes in big-endian order
    for (i = 0; i < DIR_SIZE; i++) {
        value = (value << 8) | vm->mem[(p->pc + *offset + i) % MEM_SIZE];
    }
    *offset += DIR_SIZE;
    return value;
}

int handle_indirect(program_t *p, vm_t *vm, int *offset, int mod_idx)
{
    unsigned short idx = 0;
    int value = 0;
    int i;

    // Read 2 bytes in big-endian order
    for (i = 0; i < IND_SIZE; i++) {
        idx = (idx << 8) | vm->mem[(p->pc + *offset + i) % MEM_SIZE];
    }
    *offset += IND_SIZE;

    if (mod_idx) {
        idx = idx % IDX_MOD;
    }

    // Read 4 bytes at the calculated address in big-endian order
    for (i = 0; i < DIR_SIZE; i++) {
        value = (value << 8) | vm->mem[(p->pc + idx + i) % MEM_SIZE];
    }
    return value;
}
