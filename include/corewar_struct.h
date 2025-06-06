/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** corewar_struct
*/

#ifndef COREWAR_STRUCT_H
    #define COREWAR_STRUCT_H

    #include "op.h"

// Forward declaration to resolve circular dependency
typedef struct program program_t;

typedef struct vm {
    unsigned char mem[MEM_SIZE];
    unsigned int cycle;
    program_t *programs;
    int dumper_cycle;
    int live_count;
} vm_t;

typedef struct program {
    header_t header;
    unsigned int cycles_to_live;
    unsigned int cycles_to_wait;
    unsigned int regs[REG_NUMBER + 1]; // extra register for Carry
    unsigned int pc;
    unsigned int running;
    unsigned int op1;
    unsigned int op2;
    unsigned int op3;
    program_t *next;
} program_t;

typedef int (*cmd_t)(program_t *, vm_t *);

typedef struct prog_load_info_s {
    char *program_bytes;
    int address;
    unsigned int prog_size;
} prog_load_info_t;

typedef struct prog_creation_info_s {
    char *program_bytes;
    header_t *header;
    int address;
    int prog_number;
} prog_creation_info_t;

typedef struct op_context_s {
    program_t *p;
    vm_t *vm;
    unsigned char op_byte;
} op_context_t;

#endif
