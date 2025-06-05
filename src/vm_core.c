/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** vm_core
*/

#include "../include/corewar.h"

vm_t *create_vm(void)
{
    vm_t *vm = (vm_t *)malloc(sizeof(vm_t));

    if (!vm) {
        return NULL;
    }
    vm->cycle = 0;
    vm->live_count = 0;
    vm->programs = NULL;
    for (int i = 0; i < MEM_SIZE; ++i) {
        vm->mem[i] = 0;
    }
    return vm;
}

int count_programs(vm_t *vm)
{
    program_t *tmp = vm->programs;
    int prog_count = 0;

    while (tmp) {
        prog_count++;
        tmp = tmp->next;
    }
    return prog_count;
}

int is_memory_block_free(vm_t *vm, int start, int prog_size)
{
    for (int k = 0; k < prog_size; k++) {
        if (vm->mem[(start + k) % MEM_SIZE] != 0) {
            return 0;
        }
    }
    return 1;
}

int find_free_space(vm_t *vm, int prog_size)
{
    for (int j = 0; j < MEM_SIZE; j++) {
        if (is_memory_block_free(vm, j, prog_size)) {
            return j;
        }
    }
    return -1;
}

int find_optimal_adress(vm_t *vm, int prog_size)
{
    int mem_part = MEM_SIZE / 4;
    int prog_count = count_programs(vm);

    if (prog_count == 0) {
        return 0;  // First program always starts at 0
    }
    int start_adress = (prog_count * mem_part) % MEM_SIZE;

    // Check if the calculated address is free
    if (is_memory_block_free(vm, start_adress, prog_size)) {
        return start_adress;
    }
    // If not free, find the next free block
    return find_free_space(vm, prog_size);
}
