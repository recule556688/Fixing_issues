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

#endif
