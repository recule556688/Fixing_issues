/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-iuliia.dabizha
** File description:
** struct
*/

#ifndef INCLUDED_STRUCT_H
    #define INCLUDED_STRUCT_H

typedef struct node {
    int x;
    int y;
    char *id;
    edge_t *root_edge;
    node_t *next_node;
} node_t;

typedef struct edge {
    node_t *a;
    node_t *b;
    float length;
    edge_t *next_edge;
} edge_t;

typedef struct labyrinth {
    node_t *root;
    node_t *tail;
    int robots;
} labyrinth_t;

#endif
