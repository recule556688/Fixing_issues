/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** vm_program
*/

#include "../include/corewar.h"

int check_program(vm_t *vm, program_t *p)
{
    if (p->running != 0) {
        if (p->cycles_to_wait > 0) {
            --p->cycles_to_wait;
        } else {
            run_command(vm, p);
            fetch_command(vm, p);
        }
    } else {
        p->running = 1;
        fetch_command(vm, p);
    }
    return 0;
}

void execute_programs(vm_t *vm, int *finish)
{
    program_t *p = vm->programs;

    while (p) {
        *finish = check_program(vm, p);
        p = p->next;
    }
}
