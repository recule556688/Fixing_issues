/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** program_management
*/

#include "../include/corewar.h"

void add_program(vm_t *vm, program_t *program)
{
    program_t *t = vm->programs;

    if (t != NULL) {
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = program;
    } else {
        vm->programs = program;
    }
}

program_t *initialize_program(int adress, int prog_number)
{
    program_t *program = (program_t *)malloc(sizeof(program_t));

    if (!program) {
        return NULL;
    }
    for (int j = 0; j <= REG_NUMBER; ++j) {
        program->regs[j] = 0;
    }
    program->running = 1;
    program->pc = adress % MEM_SIZE;  // Ensure PC is within memory bounds
    program->cycles_to_live = CYCLE_TO_DIE;
    program->cycles_to_wait = 0;
    program->regs[1] = prog_number;
    program->next = NULL;
    my_printf("Debug: Initialized program with PC=%d\n", program->pc);
    return program;
}

static void set_program_header(program_t *program, header_t *header)
{
    program->header = *header;
}

void load_program_to_memory(vm_t *vm, program_t *program,
    char *program_bytes, int adress)
{
    int len;

    my_printf("Debug: Loading program of size %d at address %d\n",
        program->header.prog_size, adress);
    if (program->header.prog_size <= 0) {
        my_printf("Error: Invalid program size: %d\n", program->header.prog_size);
        return;
    }
    if (program->header.prog_size > MEM_SIZE) {
        my_printf("Error: Program size %d exceeds memory size %d\n",
            program->header.prog_size, MEM_SIZE);
        return;
    }
    if (adress < 0 || adress >= MEM_SIZE) {
        my_printf("Error: Invalid load address: %d\n", adress);
        return;
    }
    if (adress + program->header.prog_size > MEM_SIZE) {
        my_printf("Error: Program would exceed memory bounds\n");
        return;
    }
    my_printf("Debug: Copying %d bytes to memory at address %d\n",
        program->header.prog_size, adress);
    my_memcpy(vm->mem + adress, program_bytes, program->header.prog_size);
    // Initialize the rest of the memory to 0
    for (int i = program->header.prog_size; i < MEM_SIZE - adress; i++) {
        vm->mem[adress + i] = 0;
    }
    // Ensure PC is set to the load address
    program->pc = adress % MEM_SIZE;
    my_printf("Debug: Set program PC to %d\n", program->pc);
}

program_t *create_program(vm_t *vm, char *program_bytes, header_t *header, int adress, int prog_number)
{
    program_t *program = initialize_program(adress, prog_number);

    if (!program) {
        return NULL;
    }
    set_program_header(program, header);
    load_program_to_memory(vm, program, program_bytes, adress);
    return program;
}
