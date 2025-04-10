/*
** EPITECH PROJECT, 2025
** maze.h
** File description:
** Header file for maze solver
*/
#ifndef MAZE_H_
    #define MAZE_H_

    #include <stdlib.h>
    #include "my.h"
    #include "struct.h"

typedef enum ROOM_PARSING_STATUS {
    NONE,
    START,
    END
} ROOM_PARSING_STATUS_t;

/* Function prototypes */
labyrinth_t *read_labyrinth(void);
labyrinth_t *create_empty_labyrinth(void);
void print_labyrinth(labyrinth_t *maze);
void free_labyrinth(labyrinth_t *maze);
node_t *clone_room(labyrinth_t *new_maze, labyrinth_t *old_maze, 
    node_t *original);
node_t *make_room(labyrinth_t *res, char *id, int x, int y);
int make_tunnel(labyrinth_t *res, char *x, char *y);
node_t *find_room(labyrinth_t *rs, char *id);
char *detect_sep(char *str, char sep);
#endif
