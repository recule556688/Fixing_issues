/*
** EPITECH PROJECT, 2025
** path_operations.c
** File description:
** Path operations for maze solver
*/

#include "../../include/struct.h"
#include "../../include/algo.h"
#include <stdlib.h>


path_t *create_path(void)
{
    path_t *path = malloc(sizeof(path_t));

    if (!path)
        return NULL;
    path->head = NULL;
    path->length = 0;
    return path;
}

static path_node_t *create_path_node(node_t *room)
{
    path_node_t *new_node = malloc(sizeof(path_node_t));

    if (!new_node)
        return NULL;
    new_node->room = room;
    new_node->next = NULL;
    return new_node;
}

void add_to_path(path_t *path, node_t *room)
{
    path_node_t *new_node = create_path_node(room);

    if (!new_node || !path)
        return;
    new_node->next = path->head;
    path->head = new_node;
    path->length++;
}

void free_path(path_t *path)
{
    path_node_t *current;
    path_node_t *next;

    if (!path)
        return;
    current = path->head;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    free(path);
}

static void print_path_node(path_node_t *node)
{
    my_putstr(node->room->id);
    if (node->next)
        my_putstr(" -> ");
}

void print_path(path_t *path)
{
    path_node_t *current = path->head;

    if (!path || !current) {
        my_putstr("No path found!\n");
        return;
    }
    while (current) {
        print_path_node(current);
        current = current->next;
    }
    my_putchar('\n');
}

void reverse_path(path_t *path)
{
    path_node_t *prev = NULL;
    path_node_t *current = path->head;
    path_node_t *next = NULL;

    if (!path || !current)
        return;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    path->head = prev;
}
