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
    program->pc = adress;
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

static int validate_load_address(int load_addr, unsigned int prog_size)
{
    if (load_addr < 0 || load_addr >= MEM_SIZE) {
        my_printf("Error: Invalid load address: %d\n", load_addr);
        return 84;
    }
    if (load_addr > MEM_SIZE - prog_size) {
        my_printf("Error: Program would exceed memory bounds"
            " (addr %d + size %u > %d)\n",
            load_addr, prog_size, MEM_SIZE);
        return 84;
    }
    return 0;
}

static int validate_program_load(unsigned int prog_size, int load_addr)
{
    my_printf("Debug: LPTM entry: address_param=%d,"
        " local_load_addr=%d, prog_size_param=%u, local_prog_size=%u\n",
        load_addr, load_addr, prog_size, prog_size);
    my_printf("Debug: Loading program of size %u at address %d\n",
        prog_size, load_addr);
    if (prog_size == 0) {
        my_printf("Error: Invalid program size in LPTM: %u\n",
            prog_size);
        return 84;
    }
    if (prog_size > MEM_SIZE) {
        my_printf("Error: Program size %u exceeds memory size %d\n",
            prog_size, MEM_SIZE);
        return 84;
    }
    return validate_load_address(load_addr, prog_size);
}

void load_program_to_memory(vm_t *vm, program_t *program,
    prog_load_info_t *info)
{
    if (validate_program_load(info->prog_size, info->address) != 0)
        return;
    my_printf("Debug: Copying %u bytes to memory at address %d\n",
        info->prog_size, info->address);
    for (unsigned int i = 0; i < info->prog_size; i++) {
        vm->mem[(info->address + i) % MEM_SIZE] = info->program_bytes[i];
    }
    program->pc = info->address;
    my_printf("Debug: Set program PC to %d\n", program->pc);
}

static void print_program_debug_info(int address, int prog_number,
    header_t *header_param, unsigned int confirmed_prog_size)
{
    my_printf("Debug: create_program received address: %d,"
        " prog_number: %d, header_param->prog_size(raw): %d\n",
        address, prog_number, header_param->prog_size);
    my_printf("Debug: create_program after set_program_header,"
        " program->header.prog_size: %u, captured confirmed_prog_size: %u\n",
        header_param->prog_size, confirmed_prog_size);
    my_printf("Debug: create_program calling LPTM with address: %d,"
        " confirmed_prog_size: %u\n",
        address, confirmed_prog_size);
}

program_t *create_program(vm_t *vm, prog_creation_info_t *info)
{
    program_t *program = NULL;
    unsigned int confirmed_prog_size = 0;
    prog_load_info_t load_info;

    print_program_debug_info(info->address, info->prog_number,
        info->header, confirmed_prog_size);
    program = initialize_program(info->address, info->prog_number);
    if (!program) {
        my_printf("Error: initialize_program failed in create_program\n");
        return NULL;
    }
    set_program_header(program, info->header);
    confirmed_prog_size = program->header.prog_size;
    load_info.program_bytes = info->program_bytes;
    load_info.address = info->address;
    load_info.prog_size = confirmed_prog_size;
    load_program_to_memory(vm, program, &load_info);
    return program;
}
