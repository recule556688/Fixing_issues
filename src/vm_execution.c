/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** vm_execution
*/

#include "../include/corewar.h"

op_t *find_command(int opcode)
{
    int i = 0;

    while (op_tab[i].mnemonique != NULL) {
        if (op_tab[i].code == opcode) {
            return (op_t *)&op_tab[i];
        }
        ++i;
    }
    return NULL;
}

void fetch_command(vm_t *vm, program_t *p)
{
    int opcode = vm->mem[p->pc];
    op_t *cmd = find_command(opcode);

    if (cmd != NULL) {
        p->cycles_to_wait = cmd->nbr_cycles;
        my_printf("Debug: Found command %s at PC=%d, cycles=%d\n",
            cmd->mnemonique, p->pc, cmd->nbr_cycles);
    } else {
        p->cycles_to_wait = 1;
        my_printf("Warning: Invalid opcode 0x%x at position %d, skipping\n",
            opcode, p->pc);
        p->pc = (p->pc + 1) % MEM_SIZE;
    }
}

static void execute_arithmetic_opcodes(vm_t *vm, program_t *p,
    unsigned char opcode)
{
    switch (opcode) {
        case 4:
            add(p, vm);
            break;
        case 5:
            sub(p, vm);
            break;
        case 6:
            and_f(p, vm);
            break;
        case 7:
            or_f(p, vm);
            break;
        case 8:
            xor_f(p, vm);
            break;
        default:
            break;
    }
}

static void execute_opcode(vm_t *vm, program_t *p, unsigned char opcode)
{
    switch (opcode) {
        case 1:
            live(p, vm);
            break;
        case 2:
            do_ld(p, vm);
            break;
        case 3:
            do_st(p, vm);
            break;
        default:
            execute_arithmetic_opcodes(vm, p, opcode);
            break;
    }
}

static void execute_memory_opcodes(vm_t *vm, program_t *p,
    unsigned char opcode)
{
    switch (opcode) {
        case 9:
            zjmp(p, vm);
            break;
        case 10:
            ldi(p, vm);
            break;
        case 11:
            sti(p, vm);
            break;
        case 12:
            fork_program(p, vm);
            break;
        default:
            break;
    }
}

static void execute_extended_opcodes(vm_t *vm, program_t *p,
    unsigned char opcode)
{
    switch (opcode) {
        case 13:
            lld(p, vm);
            break;
        case 14:
            lldi(p, vm);
            break;
        case 15:
            lfork(p, vm);
            break;
        case 16:
            aff(p, vm);
            break;
        default:
            break;
    }
}

static void execute_opcode_switch(vm_t *vm, program_t *p, unsigned char opcode)
{
    if (opcode >= 1 && opcode <= 3)
        execute_opcode(vm, p, opcode);
    if (opcode >= 4 && opcode <= 8)
        execute_arithmetic_opcodes(vm, p, opcode);
    if (opcode >= 9 && opcode <= 12)
        execute_memory_opcodes(vm, p, opcode);
    if (opcode >= 13 && opcode <= 16)
        execute_extended_opcodes(vm, p, opcode);
}

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

static void update_pc_and_print(program_t *p, vm_t *vm, unsigned char opcode)
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

void run_command(vm_t *vm, program_t *p)
{
    unsigned char opcode = vm->mem[p->pc];
    op_t *cmd = find_command(opcode);
    int initial_pc = p->pc;

    if (!cmd) {
        my_printf("Warning: Invalid opcode 0x%x at PC=%d, skipping byte\n",
            opcode, p->pc);
        p->pc = (p->pc + 1) % MEM_SIZE;
        return;
    }
    my_printf("Debug: Executing opcode 0x%x (%s) at PC=%d\n",
        opcode, cmd->mnemonique, p->pc);
    execute_opcode_switch(vm, p, opcode);
    if (p->pc == initial_pc)
        update_pc_and_print(p, vm, opcode);
}
