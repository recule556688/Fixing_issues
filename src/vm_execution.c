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
        if (p->pc == initial_pc) {
        int instruction_size = 1;
        if (opcode != 1 && opcode != 9 && opcode != 12 && opcode != 15) {
            instruction_size++;
            unsigned char coding_byte = vm->mem[(p->pc + 1) % MEM_SIZE];
            for (int i = 0; i < 3; i++) {
                unsigned char param_type = (coding_byte >> (6 - i * 2)) & 0x3;
                if (param_type == 0) continue;
                if (param_type == T_REG) {
                    instruction_size += 1;
                } else if (param_type == T_DIR) {
                    instruction_size += (opcode == 2 || opcode == 13) ? 4 : 2;
                } else if (param_type == T_IND) {
                    instruction_size += 2;
                }
            }
        } else {
            switch (opcode) {
                case 1:
                    instruction_size += 4;
                    break;
                case 9:
                case 12:
                case 15:
                    instruction_size += 2;
                    break;
            }
        }
        p->pc = (p->pc + instruction_size) % MEM_SIZE;
        my_printf("Debug: Updated PC to %d (instruction size: %d)\n",
            p->pc, instruction_size);
    }
}
