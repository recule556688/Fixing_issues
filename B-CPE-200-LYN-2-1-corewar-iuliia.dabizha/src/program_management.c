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
    return program;
}

static void set_program_header(program_t *program, char *program_bytes)
{
    unsigned char size_bytes[4];

    my_memcpy(&(program->header.magic), program_bytes, MAGIC_SIZE);
    my_memcpy(size_bytes, program_bytes + OFS_PROGSIZE, 4);
    program->header.prog_size = (size_bytes[0] << 24) | (size_bytes[1] << 16) |
        (size_bytes[2] << 8) | size_bytes[3];
    my_printf("Debug: Program size in create_program: %d\n",
        program->header.prog_size);
    my_strcpy(program->header.prog_name, program_bytes + OFS_NAME);
    my_strcpy(program->header.comment, program_bytes + OFS_COMMENT);
}

void load_program_to_memory(vm_t *vm, program_t *program,
    char *program_bytes, int adress)
{
    int len;

    if (program->header.prog_size > 0 && program->header.prog_size <= 682 &&
        program->header.prog_size < MEM_SIZE) {
        my_memcpy(vm->mem + adress, program_bytes,
            program->header.prog_size);
    } else {
        my_printf("Warning: Invalid program size: %d, using fallback\n",
            program->header.prog_size);
        len = 0;
        while (len < 682 && program_bytes[len] != 0 &&
            len < MEM_SIZE - adress) {
            len++;
        }
        my_printf("Debug: Using fallback program size: %d\n", len);
        my_memcpy(vm->mem + adress, program_bytes, len);
        program->header.prog_size = len;
    }
}

program_t *create_program(vm_t *vm, char *program_bytes,
    int adress, int prog_number)
{
    program_t *program = initialize_program(adress, prog_number);

    if (!program) {
        return NULL;
    }
    set_program_header(program, program_bytes);
    load_program_to_memory(vm, program, program_bytes, adress);
    return program;
}
