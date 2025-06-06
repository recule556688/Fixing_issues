/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** vm_cycle
*/

#include "../include/corewar.h"
#include "../include/op.h"

void handle_cycle_to_die(vm_t *vm, int *cycles_to_die,
    int *check_counter, int *cycle_counter)
{
    program_t *p = vm->programs;

    while (p) {
        if (p->cycles_to_live <= 0) {
            p->running = 0;
            my_printf("Program %s has died\n", p->header.prog_name);
        } else {
            p->cycles_to_live = *cycles_to_die;
        }
        p = p->next;
    }
    if (vm->live_count >= NBR_LIVE || *check_counter >= MAX_CHECKS) {
        *cycles_to_die -= CYCLE_DELTA;
        *check_counter = 0;
        my_printf("CYCLE_TO_DIE decreased to %d\n", *cycles_to_die);
    }
    *cycle_counter = 0;
    vm->live_count = 0;
}

int check_if_programs_running(vm_t *vm)
{
    program_t *p = vm->programs;

    while (p) {
        if (p->running) {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

static void print_hex(unsigned char str)
{
    unsigned char a[2];

    a[0] = (str / 16) + '0';
    if (a[0] > '9') {
        a[0] += 7;
    }
    a[1] = (str & 0xF) + '0';
    if (a[1] > '9') {
        a[1] += 7;
    }
    write(1, a, 2);
}

void do_dump(unsigned char *mem)
{
    int k = 0;

    for (int i = 0; i < (MEM_SIZE / 32); ++i) {
        for (int j = 0; j < 32; ++j) {
            print_hex(mem[k]);
            ++k;
        }
        write(1, "\n", 1);
    }
}

int scheduler_aux(vm_t *vm, int *cycle_counter,
    int *check_counter, int *finish)
{
    int cycle_to_die = CYCLE_TO_DIE;

    if (vm->cycle % 1000 == 0) {
        my_printf("Executing cycle %d\n", vm->cycle);
    }
    if (*cycle_counter >= CYCLE_TO_DIE) {
        handle_cycle_to_die(vm, &cycle_to_die,
            check_counter, cycle_counter);
        *finish = !check_if_programs_running(vm);
    }
    if (vm->cycle == vm->dumper_cycle) {
        do_dump(vm->mem);
    }
    return 0;
}

int scheduler(vm_t *vm)
{
    int finish = 0;
    int cycles_to_die = CYCLE_TO_DIE;
    int cycle_counter = 0;
    int check_counter = 0;
    int max_cycles = 10000;

    vm->cycle = 0;
    while (finish == 0 && vm->cycle < max_cycles) {
        execute_programs(vm, &finish);
        ++vm->cycle;
        ++cycle_counter;
        scheduler_aux(vm, &cycle_counter, &check_counter, &finish);
    }
    if (vm->cycle >= max_cycles) {
        my_printf("Maximum cycle count reached (%d)."
            " Stopping execution.\n", max_cycles);
    }
    return 0;
}
