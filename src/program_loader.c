/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** program_loader
*/

#include "../include/corewar.h"

static int read_file_into_buffer(char *filename, char *buffer)
{
    FILE *f = fopen(filename, "rb");
    int bytes_read;

    if (!f) {
        my_printf("Error: Could not open file %s\n", filename);
        return -1;
    }
    bytes_read = fread(buffer, 1, MEM_SIZE + OFS_CODE, f);
    fclose(f);
    if (bytes_read <= 0) {
        my_printf("Error: Failed to read file or file is empty\n");
        return -1;
    }
    return bytes_read;
}

static int validate_magic_number(unsigned char *tmp)
{
    unsigned int magic = 0;
    unsigned char magic_bytes[4];
    unsigned int reversed_magic;

    my_memcpy(magic_bytes, tmp, MAGIC_SIZE);
    magic = (magic_bytes[0] << 24) | (magic_bytes[1] << 16) |
        (magic_bytes[2] << 8) | magic_bytes[3];
    reversed_magic = (magic_bytes[3] << 24) | (magic_bytes[2] << 16) |
        (magic_bytes[1] << 8) | magic_bytes[0];
    my_printf("Debug: Magic number read: 0x%x, Expected: 0x%x\n",
        magic, COREWAR_EXEC_MAGIC);
    if (magic != COREWAR_EXEC_MAGIC && reversed_magic != COREWAR_EXEC_MAGIC) {
        my_printf("Error: Invalid magic number in the champion file\n");
        return -1;
    }
    return 0;
}

static unsigned int get_program_size(unsigned char *tmp)
{
    unsigned char size_bytes[4];
    unsigned int prog_size;

    my_memcpy(size_bytes, tmp + OFS_PROGSIZE, 4);
    prog_size = (size_bytes[0] << 24) | (size_bytes[1] << 16) |
        (size_bytes[2] << 8) | size_bytes[3];
    my_printf("Debug: Program size read: %u bytes\n", prog_size);
    if (prog_size > 682) {
        my_printf("Warning: Program size too large (%u),"
        " maximum is 682 bytes\n", prog_size);
    }
    return prog_size;
}

static int find_address(vm_t *vm, int prog_size, int adress)
{
    if (adress < 0) {
        adress = find_optimal_adress(vm, prog_size);
        if (adress < 0) {
            my_printf("Error: Could not find optimal"
                " address for the program\n");
            return -1;
        }
    }
    return adress;
}

static int load_file_to_buffer(char *filename, char *tmp)
{
    int bytes_read = read_file_into_buffer(filename, tmp);

    if (bytes_read < 0) {
        return -1;
    }
    return 0;
}

static int check_magic_number(char *tmp)
{
    if (validate_magic_number((unsigned char *)tmp) < 0) {
        return -1;
    }
    return 0;
}

static int calculate_address(vm_t *vm, unsigned int prog_size, int adress)
{
    adress = find_address(vm, prog_size, adress);
    if (adress < 0) {
        return -1;
    }
    return adress;
}

static program_t *init_program(vm_t *vm, char *tmp,
    int adress, int prog_number)
{
    program_t *program = create_program(vm, tmp, adress, prog_number);

    if (!program) {
        my_printf("Error: Failed to create program\n");
        return NULL;
    }
    return program;
}

program_t *load_program(vm_t *vm, char *filename, int adress, int prog_number)
{
    program_t *program;
    char tmp[MEM_SIZE + OFS_CODE];
    unsigned int prog_size;

    if (load_file_to_buffer(filename, tmp) < 0) {
        return NULL;
    }
    if (check_magic_number(tmp) < 0) {
        return NULL;
    }
    prog_size = get_program_size((unsigned char *)tmp);
    adress = calculate_address(vm, prog_size, adress);
    if (adress < 0) {
        return NULL;
    }
    program = init_program(vm, tmp, adress, prog_number);
    if (!program)
        return NULL;
    add_program(vm, program);
    return program;
}
