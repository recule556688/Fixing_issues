/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** ger_parameter_value_handle
*/

#include "../include/corewar.h"

int get_parameter_value_one(program_t *p, vm_t *vm, int *offset, int mod_idx)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned char type = (op_byte >> 6) & 0x3;

    my_printf("Debug: Parameter 1 type: 0x%x\n", type);
    if (type == T_REG) {
        return handle_register(p, vm, offset);
    }
    if (type == T_DIR) {
        return handle_direct(p, vm, offset);
    }
    if (type == T_IND) {
        return handle_indirect(p, vm, offset, mod_idx);
    }
    return 0;
}

int get_parameter_value_two(program_t *p, vm_t *vm, int *offset, int mod_idx)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned char type = (op_byte >> 4) & 0x3;

    my_printf("Debug: Parameter 2 type: 0x%x\n", type);
    if (type == T_REG) {
        return handle_register(p, vm, offset);
    }
    if (type == T_DIR) {
        return handle_direct(p, vm, offset);
    }
    if (type == T_IND) {
        return handle_indirect(p, vm, offset, mod_idx);
    }
    return 0;
}

int get_parameter_value_three(program_t *p, vm_t *vm, int *offset, int mod_idx)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned char type = (op_byte >> 2) & 0x3;

    my_printf("Debug: Parameter 3 type: 0x%x\n", type);
    if (type == T_REG) {
        return handle_register(p, vm, offset);
    }
    if (type == T_DIR) {
        return handle_direct(p, vm, offset);
    }
    if (type == T_IND) {
        return handle_indirect(p, vm, offset, mod_idx);
    }
    return 0;
}
