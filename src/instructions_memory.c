/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** instructions_memory
*/

#include "../include/corewar.h"
#include "../include/my.h"

int live(program_t *p, vm_t *vm)
{
    int player_number = 0;
    int i;

    for (i = 0; i < DIR_SIZE; i++) {
        player_number = (player_number << 8) |
            vm->mem[(p->pc + 1 + i) % MEM_SIZE];
    }
    my_printf("The player %d(%s) is alive\n",
        player_number, p->header.prog_name);
    p->pc = (p->pc + 5) % MEM_SIZE;
    p->cycles_to_live = CYCLE_TO_DIE;
    ++vm->live_count;
    return 0;
}

static int extract_value(program_t *p, vm_t *vm, unsigned char op_byte,
    unsigned int *value)
{
    int offset = 2;
    unsigned short idx;

    if (((op_byte >> 6) & 0x3) == T_DIR) {
        *value = *((int *)(vm->mem + p->pc + offset));
        offset += DIR_SIZE;
    } else if (((op_byte >> 6) & 0x3) == T_IND) {
        idx = *((unsigned short *)(vm->mem + p->pc + offset));
        idx = idx % IDX_MOD;
        *value = *((int *)(vm->mem + (p->pc + idx) % MEM_SIZE));
        offset += IND_SIZE;
    } else {
        p->pc = (p->pc + 1) % MEM_SIZE;
        return -1;
    }
    return offset;
}

static int handle_ld_register(program_t *p, vm_t *vm, unsigned char op_byte,
    unsigned int value, int offset)
{
    unsigned int reg_num;

    if (((op_byte >> 4) & 0x3) == T_REG) {
        reg_num = vm->mem[p->pc + offset];
        if (reg_num >= 1 && reg_num <= REG_NUMBER) {
            p->regs[reg_num] = value;
            p->regs[0] = (value == 0) ? 1 : 0;
            my_printf("Debug: LD stored value %d in register %d\n",
                value, reg_num);
            return offset + 1;
        } else {
            my_printf("Error: Invalid register number %d for LD\n", reg_num);
        }
    } else {
        my_printf("Error: Invalid second parameter type for LD\n");
    }
    return offset;
}

static int handle_ld_parameter(program_t *p, vm_t *vm, unsigned char op_byte,
    unsigned int *value, int *offset)
{
    if (((op_byte >> 6) & 0x3) == T_DIR) {
        *value = handle_direct(p, vm, offset);
        my_printf("Debug: LD direct value: %d\n", *value);
        return 0;
    } else if (((op_byte >> 6) & 0x3) == T_IND) {
        *value = handle_indirect(p, vm, offset, 1);
        my_printf("Debug: LD indirect value: %d\n", *value);
        return 0;
    } else {
        my_printf("Error: Invalid first parameter type for LD\n");
        p->pc = (p->pc + 1) % MEM_SIZE;
        return -1;
    }
}

int do_ld(program_t *p, vm_t *vm)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned int value;
    int offset = 2;
    int start_pc = p->pc;

    my_printf("Debug: LD instruction at PC=%d,"
        " coding byte=0x%x\n", p->pc, op_byte);
    if (handle_ld_parameter(p, vm, op_byte, &value, &offset) == -1)
        return 0;
    offset = handle_ld_register(p, vm, op_byte, value, offset);
    p->pc = (start_pc + offset) % MEM_SIZE;
    my_printf("Debug: LD PC updated from %d to %d (size: %d)\n",
        start_pc, p->pc, offset);
    return 0;
}

static int handle_source_register(program_t *p, vm_t *vm,
    unsigned char op_byte, unsigned int *reg_num)
{
    int offset = 2;

    if (((op_byte >> 6) & 0x3) == T_REG) {
        *reg_num = vm->mem[p->pc + offset];
        if (*reg_num < 1 || *reg_num > REG_NUMBER) {
            p->pc = (p->pc + 1) % MEM_SIZE;
            return -1;
        }
        return offset + 1;
    } else {
        p->pc = (p->pc + 1) % MEM_SIZE;
        return -1;
    }
}

static int handle_target_register(program_t *p, vm_t *vm,
    unsigned int reg_num, int offset)
{
    unsigned int target_reg;
    unsigned short idx;
    unsigned char op_byte = vm->mem[p->pc + 1];

    if (((op_byte >> 4) & 0x3) == T_REG) {
        target_reg = vm->mem[p->pc + offset];
        if (target_reg >= 1 && target_reg <= REG_NUMBER) {
            p->regs[target_reg] = p->regs[reg_num];
        }
        offset += 1;
    } else if (((op_byte >> 4) & 0x3) == T_IND) {
        idx = *((unsigned short *)(vm->mem + p->pc + offset));
        idx = idx % IDX_MOD;
        *((int *)(vm->mem + (p->pc + idx) % MEM_SIZE)) = p->regs[reg_num];
        offset += IND_SIZE;
    }
    return offset;
}

int do_st(program_t *p, vm_t *vm)
{
    unsigned char op_byte = vm->mem[p->pc + 1];
    unsigned int reg_num;
    int offset;

    offset = handle_source_register(p, vm, op_byte, &reg_num);
    if (offset == -1) {
        return 0;
    }
    offset = handle_target_register(p, vm, reg_num, offset);
    p->pc = (p->pc + offset) % MEM_SIZE;
    return 0;
}
