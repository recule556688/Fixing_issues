/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** Main file for the corewar program
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include "../include/corewar.h"
#include "../include/my.h"

static void print_help(void)
{
    my_printf("USAGE\n");
    my_printf("\t./corewar [-dump nbr_cycle] [[-n prog_number]"
        " [-a load_address] ");
    my_printf("prog_name] ...\n\n");
    my_printf("DESCRIPTION\n");
    my_printf("\t-dump nbr_cycle\tdumps the memory after"
        " the nbr_cycle execution ");
    my_printf("(if the round isn't\n\t\t\talready over)"
        " with the following format: ");
    my_printf("32 bytes/line\n\t\t\tin hexadecimal (A0BCDEFF1DD3...)\n");
    my_printf("\t-n prog_number\tsets the next program's number. ");
    my_printf("By default, the first free number"
        "\n\t\t\tin the parameter order\n");
    my_printf("\t-a load_address\tsets the next program's loading address. ");
    my_printf("When no address is\n\t\t\tspecified,"
        " optimize the addresses so that the ");
    my_printf("processes are as far\n\t\t\taway"
        " from each other as possible. ");
    my_printf("The addresses are modulo MEM_SIZE\n");
}

static int read_program_code(int fd, header_t *header, unsigned char *buffer,
    char *filename)
{
    int ret = read(fd, buffer, header->prog_size);
    unsigned char dummy;

    if (ret < 0) {
        my_printf("Error: Failed to read from file %s\n", filename);
        return 84;
    }
    if (ret < (int)header->prog_size) {
        my_printf("Error: File %s is corrupted (read %d bytes, expected %d)\n",
            filename, ret, header->prog_size);
        return 84;
    }
    if (read(fd, &dummy, 1) > 0) {
        my_printf("Error: File %s is too large"
            " (program size mismatch)\n", filename);
        return 84;
    }
    my_printf("Debug: Successfully read %d bytes of program code\n", ret);
    my_printf("Debug: First few bytes: 0x%02x 0x%02x 0x%02x 0x%02x\n",
        buffer[0], buffer[1], buffer[2], buffer[3]);
    return 0;
}

static int load_program_file(char *filename, vm_t *vm,
    int prog_nbr, int address)
{
    int fd = open(filename, O_RDONLY);
    header_t header;
    unsigned char *buffer = NULL;
    int ret = 0;
    program_t *program;

    if (fd == -1) {
        my_printf("Error: Can't open %s\n", filename);
        return 84;
    }
    if (read_champion_header(fd, &header, filename) == 84) {
        close(fd);
        return 84;
    }
    my_printf("Debug: Reading program code of size %d\n", header.prog_size);
    buffer = malloc(header.prog_size);
    if (!buffer) {
        my_printf("Error: Memory allocation failed\n");
        close(fd);
        return 84;
    }
    if (read_program_code(fd, &header, buffer, filename) != 0) {
        free(buffer);
        close(fd);
        return 84;
    }
    my_printf("Debug: Creating program at address %d\n", address);
    program = create_program(vm, (char *)buffer, &header, address, prog_nbr);
    free(buffer);
    if (!program) {
        close(fd);
        return 84;
    }
    add_program(vm, program);
    close(fd);
    return 0;
}

int parse_args_aux(char **arg, int *next_prog_nbr,
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

static int parse_args(int argc, char **argv, vm_t *vm)
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

static int initialize_vm(int argc, char **argv, vm_t **vm)
{
    if (argc <= 1) {
        print_help();
        return 0;
    }
    if (argc < 1)
        return 84;
    *vm = create_vm();
    if (!*vm)
        return 84;
    if (parse_args(argc, argv, *vm) != 0) {
        free(*vm);
        return 84;
    }
    if (!(*vm)->programs) {
        my_printf("Error: No champion loaded\n");
        free(*vm);
        return 84;
    }
    return 1;
}

int main(int argc, char **argv)
{
    vm_t *vm;
    int init_result;

    init_result = initialize_vm(argc, argv, &vm);
    if (init_result == 84) {
        return 84;
    }
    if (init_result == 0) {
        return 0;
    }
    scheduler(vm);
    free(vm);
    return 0;
}
