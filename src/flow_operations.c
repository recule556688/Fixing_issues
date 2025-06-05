/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** assembler_interpretator
*/

#include "../include/corewar.h"

int zjmp(program_t *p, vm_t *vm)
{
    short offset;

    if (p->regs[0] == 1) {
        // Read the offset in big-endian format
        offset = (vm->mem[(p->pc + 1) % MEM_SIZE] << 8) | 
                vm->mem[(p->pc + 2) % MEM_SIZE];
        // Apply IDX_MOD and update PC
        p->pc = (p->pc + (offset % IDX_MOD)) % MEM_SIZE;
        my_printf("Debug: zjmp jumping to PC=%d (offset=%d)\n", p->pc, offset);
    } else {
        p->pc = (p->pc + 3) % MEM_SIZE;
        my_printf("Debug: zjmp not jumping, carry=0, PC=%d\n", p->pc);
    }
    return 0;
}

int ldi(program_t *p, vm_t *vm)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    int value1;
    int value2;
    int address;
    int reg_dest;
    int offset = 2;

    value1 = get_parameter_value_one(p, vm, &offset, 1);
    value2 = get_parameter_value_two(p, vm, &offset, 1);
    address = (p->pc + ((value1 + value2) % IDX_MOD)) % MEM_SIZE;
    if (((op_byte >> 2) & 0x3) == T_REG) {
        reg_dest = vm->mem[p->pc + offset];
        if (reg_dest >= 1 && reg_dest <= REG_NUMBER) {
            p->regs[reg_dest] = *((int *)(vm->mem + address));
        }
        offset += 1;
    }
    p->pc = (p->pc + offset) % MEM_SIZE;
    return 0;
}

int validate_register_and_update_pc(program_t *p, vm_t *vm, int *offset,
    unsigned char op_byte)
{
    int reg_src;

    if (((op_byte >> 6) & 0x3) == T_REG) {
        reg_src = vm->mem[p->pc + *offset];
        if (reg_src < 1 || reg_src > REG_NUMBER) {
            p->pc = (p->pc + 1) % MEM_SIZE;
            return 0;
        }
        *offset += 1;
    } else {
        p->pc = (p->pc + 1) % MEM_SIZE;
        return 0;
    }
    return reg_src;
}

int sti(program_t *p, vm_t *vm)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    int value1;
    int value2;
    int address;
    int offset = 2;
    int reg_src = validate_register_and_update_pc(p, vm, &offset, op_byte);

    if (reg_src == 0) {
        return 0;
    }
    value1 = get_parameter_value_two(p, vm, &offset, 1);
    value2 = get_parameter_value_three(p, vm, &offset, 1);
    address = (p->pc + ((value1 + value2) % IDX_MOD)) % MEM_SIZE;
    *((int *)(vm->mem + address)) = p->regs[reg_src];
    p->pc = (p->pc + offset) % MEM_SIZE;
    return 0;
}
