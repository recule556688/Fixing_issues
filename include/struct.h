/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-iuliia.dabizha
** File description:
** Data structures for maze/labyrinth implementation
*/

#ifndef INCLUDED_STRUCT_H
    #define INCLUDED_STRUCT_H

typedef struct edge edge_t;
typedef struct node node_t;

typedef struct node {
    int x;              /* Position coordinates */
    int y;
    char *id;          /* Room identifier */
    edge_t *root_edge; /* Linked list of edges connecting to other nodes */
    node_t *next_node;
} node_t;

typedef struct edge {
    node_t *a;         /* Source node */
    node_t *b;         /* Destination node */
    float length;      /* Edge length/distance */
    edge_t *next_edge;
} edge_t;

typedef struct labyrinth {
    node_t *root;      /* First room in the labyrinth */
    node_t *tail;      /* Last room added */
    node_t *start;     /* Starting room */
    node_t *end;       /* End/goal room */
    int robots;        /* Number of robots */
} labyrinth_t;

#endif