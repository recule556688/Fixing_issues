/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-iuliia.dabizha
** File description:
** Memory management functions
*/

#include "../include/maze.h"

static void free_edges(edge_t *edge)
{
    edge_t *next;

    while (edge) {
        next = edge->next_edge;
        free(edge);
        edge = next;
    }
}

static void free_nodes(node_t *node)
{
    node_t *next;

    while (node) {
        next = node->next_node;
        free_edges(node->root_edge);
        free(node->id);
        free(node);
        node = next;
    }
}

void free_labyrinth(labyrinth_t *maze)
{
    if (!maze)
        return;
    free_nodes(maze->root);
    free(maze);
}
