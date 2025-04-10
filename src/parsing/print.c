/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-iuliia.dabizha
** File description:
** Print functions
*/

#include "../include/maze.h"

static void print_header(labyrinth_t *maze)
{
    node_t *current = maze->root;

    my_putchar(' ');
    while (current) {
        my_putchar(' ');
        my_putstr(current->id);
        my_putchar(' ');
        current = current->next_node;
    }
    my_putchar('\n');
}

static float get_edge_length(node_t *from, node_t *to)
{
    edge_t *edge = from->root_edge;

    while (edge) {
        if (edge->b == to)
            return edge->length;
        edge = edge->next_edge;
    }
    return -1;
}

void print_labyrinth(labyrinth_t *maze)
{
    node_t *row = maze->root;
    node_t *col;
    float length;

    if (!maze || !maze->root)
        return;

    print_header(maze);
    while (row) {
        my_putstr(row->id);
        col = maze->root;
        while (col) {
            my_putchar(' ');
            length = get_edge_length(row, col);
            if (length < 0) {
                my_putstr("- ");
            } else {
                if (length < 10)
                    my_putchar(' ');
                my_putfloat(length, 1);
                my_putchar(' ');
            }
            col = col->next_node;
        }
        my_putchar('\n');
        row = row->next_node;
    }
} 