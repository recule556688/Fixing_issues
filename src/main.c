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
        my_printf("Error: File %s is too large\n", filename);
        return 84;
    }
    my_printf("Debug: Successfully read %d bytes of program code\n", ret);
    my_printf("Debug: First few bytes: 0x%02x 0x%02x 0x%02x 0x%02x\n",
        buffer[0], buffer[1], buffer[2], buffer[3]);
    return 0;
}

static int allocate_and_read_buffer(int fd, header_t *header,
    unsigned char **buffer, char *filename)
{
    my_printf("Debug: Reading program code of size %d\n", header->prog_size);
    *buffer = malloc(header->prog_size);
    if (!*buffer) {
        my_printf("Error: Memory allocation failed\n");
        close(fd);
        return 84;
    }
    if (read_program_code(fd, header, *buffer, filename) != 0) {
        free(*buffer);
        close(fd);
        return 84;
    }
    return 0;
}

static int create_and_add_program(vm_t *vm, prog_creation_info_t *info)
{
    program_t *program;

    my_printf("Debug: Creating program at address %d\n", info->address);
    program = create_program(vm, info);
    if (!program) {
        return 84;
    }
    add_program(vm, program);
    return 0;
}

static int open_and_read_program(char *filename, int *fd,
    header_t *header, unsigned char **buffer)
{
    *fd = open(filename, O_RDONLY);
    if (*fd == -1)
        return 84;
    if (read_champion_header(*fd, header, filename) == 84) {
        close(*fd);
        return 84;
    }
    if (allocate_and_read_buffer(*fd, header, buffer, filename) != 0) {
        close(*fd);
        return 84;
    }
    return 0;
}

int load_program_file(char *filename, vm_t *vm,
    int prog_nbr, int address)
{
    int fd = 0;
    header_t header;
    unsigned char *buffer = NULL;
    prog_creation_info_t info;

    if (open_and_read_program(filename, &fd, &header, &buffer) != 0)
        return 84;
    info.program_bytes = (char *)buffer;
    info.header = &header;
    info.address = address;
    info.prog_number = prog_nbr;
    if (create_and_add_program(vm, &info) != 0) {
        free(buffer);
        close(fd);
        return 84;
    }
    free(buffer);
    close(fd);
    return 0;
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
