/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** argument_parser
*/

#include "../include/corewar.h"

static int parse_args_aux(char **arg, int *next_prog_nbr,
    int *next_address, int *dump_cycle)
{
    int res = 0;

    if (my_strcmp(*arg, "-dump") == 0) {
        *dump_cycle = my_atoi(*(arg + 1));
        res = 1;
    }
    if (my_strcmp(*arg, "-n") == 0) {
        *next_prog_nbr = my_atoi(*(arg + 1));
        res = 1;
    }
    if (my_strcmp(*arg, "-a") == 0) {
        *next_address = my_atoi(*(arg + 1)) % MEM_SIZE;
        res = 1;
    }
    return res;
}

static int parse_args_aux_two(char **arg, int *next_prog_nbr,
    int *next_address, vm_t *vm)
{
    int address = *next_address;

    if (address == -1) {
        address = find_optimal_adress(vm, 0);
        my_printf("Debug: Selected optimal address: %d\n", address);
    }
    address = address % MEM_SIZE;
    my_printf("Debug: Final load address: %d\n", address);
    if (load_program_file(*arg, vm, *next_prog_nbr, address) != 0) {
        return 84;
    }
    (*next_prog_nbr)++;
    *next_address = -1;
    return 0;
}

int parse_args(int argc, char **argv, vm_t *vm)
{
    int i = 1;
    int dump_cycle = -1;
    int next_prog_nbr = 1;
    int next_address = -1;
    int program_count = 0;

    while (i < argc) {
        if (parse_args_aux(argv + i, &next_prog_nbr,
            &next_address, &dump_cycle)) {
            i += 2;
        } else {
            parse_args_aux_two(argv + i, &next_prog_nbr, &next_address, vm);
            program_count++;
            i++;
        }
    }
    vm->dumper_cycle = (unsigned int)dump_cycle;
    return (program_count == 0) ? 84 : 0;
}
