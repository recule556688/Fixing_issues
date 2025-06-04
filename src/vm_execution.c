/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** vm_execution
*/

#include "../include/corewar.h"

const op_t *find_command(int opcode)
{
    int i = 0;

    while (op_tab[i].mnemonique != NULL) {
        if (op_tab[i].code == opcode) {
            return &op_tab[i];
        }
        ++i;
    }
    return NULL;
}

void fetch_command(vm_t *vm, program_t *p)
{
    int opcode = vm->mem[p->pc];
    const op_t *cmd = find_command(opcode);

    if (cmd != NULL) {
        p->cycles_to_wait = cmd->nbr_cycles;
    } else {
        p->cycles_to_wait = 1;
        // ICI MECHANT PAS BO
        my_printf("Warning: Invalid opcodeSS 0x%x at"
            " position %d, skipping\n", opcode, p->pc);
        p->pc += 1;
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
    int initial_pc = p->pc;

    if (opcode < 1 || opcode > 16) {
        my_printf("Warning: Invalid opcode 0x%x at PC=%d, skipping byte\n",
            opcode, p->pc);
        p->pc = (p->pc + 1) % MEM_SIZE;
        return;
    }
    my_printf("Debug: Executing opcode 0x%x at PC=%d\n", opcode, p->pc);
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
    }

    if (p->pc == initial_pc) {
        p->pc = (p->pc + 1) % MEM_SIZE;
        my_printf("Debug: Instruction did not update PC, advancing by 1 to %d\n", p->pc);
    } else {
        my_printf("Debug: PC updated from %d to %d\n", initial_pc, p->pc);
    }

    if (p->pc < 0 || p->pc >= MEM_SIZE) {
        my_printf("Warning: PC out of bounds (%d), wrapping to %d\n", 
            p->pc, p->pc % MEM_SIZE);
        p->pc = p->pc % MEM_SIZE;
    }
}
