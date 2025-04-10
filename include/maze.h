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

    typedef enum ROOM_PARSING_STATUS {
        NONE, 
        START,
        END
    } ROOM_PARSING_STATUS;

    typedef struct edge edge_t;
    typedef struct node node_t;
    typedef struct labyrinth labyrinth_t;

    struct edge {
        node_t *a;         /* Source node */
        node_t *b;         /* Destination node */
        float length;      /* Edge length/distance */
        edge_t *next_edge;
    };

    struct node {
        int x;              /* Position coordinates */
        int y;
        char *id;          /* Room identifier */
        edge_t *root_edge; /* Linked list of edges connecting to other nodes */
        node_t *next_node;
    };

    struct labyrinth {
        node_t *root;      /* First room in the labyrinth */
        node_t *tail;      /* Last room added */
        node_t *start;     /* Starting room */
        node_t *end;       /* End/goal room */
        int robots;        /* Number of robots */
    };

    /* Function prototypes */
    labyrinth_t *read_labyrinth(void);
    void print_labyrinth(labyrinth_t *maze);
    void free_labyrinth(labyrinth_t *maze);
    node_t *make_room(labyrinth_t *res, char *id, int x, int y);
    void make_tunnel(labyrinth_t *res, char *x, char *y);
    node_t *find_room(labyrinth_t *rs, char *id);
    char *detect_sep(char *str, char sep);

#endif 