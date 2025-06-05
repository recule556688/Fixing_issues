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
    program->pc = adress;  // Set PC to the load address
    program->cycles_to_live = CYCLE_TO_DIE;
    program->cycles_to_wait = 0;
    program->regs[1] = prog_number;  // Set player number in register 1
    program->next = NULL;
    my_printf("Debug: Initialized program with PC=%d\n", program->pc);
    return program;
}

static void set_program_header(program_t *program, header_t *header)
{
    program->header = *header;
}

void load_program_to_memory(vm_t *vm, program_t *program,
    char *program_bytes, int address_param)
{
    int local_load_addr = address_param;
    unsigned int local_prog_size = program->header.prog_size;

    my_printf("Debug: LPTM func entry: address_param=%d, local_load_addr=%d, local_prog_size=%u\n",
        address_param, local_load_addr, local_prog_size);

    my_printf("Debug: Loading program of size %u at address %d\n",
        local_prog_size,
        local_load_addr);

    if (local_prog_size == 0) {
        my_printf("Error: Invalid program size: %u\n", local_prog_size);
        return;
    }
    if (local_prog_size > MEM_SIZE) {
        my_printf("Error: Program size %u exceeds memory size %d\n",
            local_prog_size, MEM_SIZE);
        return;
    }
    if (local_load_addr < 0 || local_load_addr >= MEM_SIZE) {
        my_printf("Error: Invalid load address: %d\n", local_load_addr);
        return;
    }
    if (local_load_addr > MEM_SIZE - local_prog_size) {
        my_printf("Error: Program would exceed memory bounds (addr %d + size %u > %d)\n", local_load_addr, local_prog_size, MEM_SIZE);
        return;
    }

    my_printf("Debug: Copying %u bytes to memory at address %d\n",
        local_prog_size,
        local_load_addr);

    for (unsigned int i = 0; i < local_prog_size; i++) {
        vm->mem[(local_load_addr + i) % MEM_SIZE] = program_bytes[i];
    }

    program->pc = local_load_addr;
    my_printf("Debug: Set program PC to %d\n", program->pc);
}

program_t *create_program(vm_t *vm, char *program_bytes, header_t *header, int adress, int prog_number)
{
    program_t *program = NULL;
    int confirmed_address = adress; // Store address to prevent overwrite if 'adress' param is fragile

    my_printf("Debug: create_program received address: %d, prog_number: %d\n", confirmed_address, prog_number);
    program = initialize_program(confirmed_address, prog_number);

    if (!program) {
        my_printf("Error: initialize_program failed in create_program\n");
        return NULL;
    }
    set_program_header(program, header);
    my_printf("Debug: create_program calling load_program_to_memory with address: %d\n", confirmed_address);
    load_program_to_memory(vm, program, program_bytes, confirmed_address);
    return program;
}
