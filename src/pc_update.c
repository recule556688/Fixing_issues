/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** pc_update
*/

#include "../include/corewar.h"

static int calculate_regular_instruction_size(unsigned char opcode,
    unsigned char coding_byte)
{
    int size = 2;
    unsigned char param_type;

    for (int i = 0; i < 3; i++) {
        param_type = (coding_byte >> (6 - i * 2)) & 0x3;
        if (param_type == 0)
            continue;
        if (param_type == T_REG)
            size += 1;
        if (param_type == T_DIR)
            size += (opcode == 2 || opcode == 13) ? 4 : 2;
        if (param_type == T_IND)
            size += 2;
    }
    return size;
}

static int calculate_special_instruction_size(unsigned char opcode)
{
    if (opcode == 1)
        return 5;
    if (opcode == 9 || opcode == 12 || opcode == 15)
        return 3;
    return 1;
}

void update_pc_and_print(program_t *p, vm_t *vm, unsigned char opcode)
{
    int instruction_size;
    unsigned char coding_byte;

    if (opcode != 1 && opcode != 9 && opcode != 12 && opcode != 15) {
        coding_byte = vm->mem[(p->pc + 1) % MEM_SIZE];
        instruction_size = calculate_regular_instruction_size(opcode,
            coding_byte);
    } else {
        instruction_size = calculate_special_instruction_size(opcode);
    }
    p->pc = (p->pc + instruction_size) % MEM_SIZE;
    my_printf("Debug: Updated PC to %d (instruction size: %d)\n",
        p->pc, instruction_size);
}
