/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** corewar
*/

#ifndef INCLUDED_COREWAR_H
    #define INCLUDED_COREWAR_H

    #include "corewar_struct.h"
    #include "op.h"
    #include <stdio.h>
    #include "my.h"
    #include <unistd.h>
    #include <stdint.h>

    #define OFS_NAME 4
    #define OFS_PROGSIZE 136 // 0x88
    #define OFS_COMMENT 140 // 0x8C
    #define OFS_CODE 2192 // 0x890
    #define MAGIC_SIZE 4


vm_t *create_vm(void);
int find_free_slot(vm_t *vm);
int find_optimal_adress(vm_t *vm, int prog_size);
program_t *load_program(vm_t *vm, char *filename, int adress, int prog_number);
int live(program_t *p, vm_t *vm);
void add_program(vm_t *vm, program_t *program);
const op_t *find_command(int opcode);
void fetch_command(vm_t *vm, program_t *p);
int check_program(vm_t *vm, program_t *p);
void execute_programs(vm_t *vm, int *finish);
void handle_cycle_to_die(vm_t *vm, int *cycles_to_die,
    int *check_counter, int *cycle_counter);
void run_command(vm_t *vm, program_t *p);
int check_if_programs_running(vm_t *vm);
int scheduler(vm_t *vm);
program_t *create_program(vm_t *vm, char *program_bytes,
    int adress, int prog_number);
int do_ld(program_t *p, vm_t *vm);
int do_st(program_t *p, vm_t *vm);
int add(program_t *p, vm_t *vm);
int sub(program_t *p, vm_t *vm);
int and_f(program_t *p, vm_t *vm);
int or_f(program_t *p, vm_t *vm);
int xor_f(program_t *p, vm_t *vm);
int zjmp(program_t *p, vm_t *vm);
int ldi(program_t *p, vm_t *vm);
int sti(program_t *p, vm_t *vm);
int fork_program(program_t *p, vm_t *vm);
int lld(program_t *p, vm_t *vm);
int lldi(program_t *p, vm_t *vm);
int lfork(program_t *p, vm_t *vm);
int aff(program_t *p, vm_t *vm);
uint32_t convert_endian(uint32_t value);
int read_champion_header(int fd, header_t *header);
void do_dump(unsigned char *mem);
int my_atoi(const char *str);
int get_parameter_value_one_g(program_t *p, vm_t *vm,
    int *offset, int mod_idx);
int get_parameter_value_two_g(program_t *p, vm_t *vm,
    int *offset, int mod_idx);
int get_parameter_value_one(program_t *p, vm_t *vm,
    int *offset, int mod_idx);
int get_parameter_value_two(program_t *p, vm_t *vm, int *offset, int mod_idx);
int get_parameter_value_three(program_t *p, vm_t *vm,
    int *offset, int mod_idx);
int get_register_value(program_t *p, vm_t *vm, int *offset);
int get_direct_value(vm_t *vm, program_t *p, int *offset);
int get_indirect_value(vm_t *vm, program_t *p,
    int *offset, int mod_idx);
int handle_register(program_t *p, vm_t *vm, int *offset);
int handle_direct(program_t *p, vm_t *vm, int *offset);
int handle_indirect(program_t *p, vm_t *vm, int *offset, int mod_idx);

//interpretation of assembler!!!!

#endif
