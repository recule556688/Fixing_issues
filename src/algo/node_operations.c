/*
** EPITECH PROJECT, 2025
** node_operations.c
** File description:
** Node operations for maze solver
*/

#include "../../include/struct.h"
#include "../../include/algo.h"
#include <stdlib.h>

int count_nodes(labyrinth_t *maze)
{
    int count = 0;
    node_t *current = maze->root;

    while (current) {
        count++;
        current = current->next_node;
    }
    return count;
}

void free_nodes_array(dijkstra_node_t **nodes, int count)
{
    int i = 0;

    if (!nodes)
        return;
    while (i < count) {
        free(nodes[i]);
        i++;
    }
    free(nodes);
}

static dijkstra_node_t *create_dijkstra_node(node_t *node, node_t *start)
{
    dijkstra_node_t *new_node = malloc(sizeof(dijkstra_node_t));

    if (!new_node)
        return NULL;
    new_node->node = node;
    new_node->dist = (node == start) ? 0 : INF_DIST;
    new_node->prev = NULL;
    new_node->visited = false;
    return new_node;
}

dijkstra_node_t **initialize_nodes(labyrinth_t *maze, node_t *start)
{
    int count = count_nodes(maze);
    dijkstra_node_t **nodes = malloc(sizeof(dijkstra_node_t *) * count);
    node_t *current = maze->root;
    int i = 0;

    if (!nodes)
        return NULL;
    while (current) {
        nodes[i] = create_dijkstra_node(current, start);
        if (!nodes[i]) {
            free_nodes_array(nodes, i);
            return NULL;
        }
        current = current->next_node;
        i++;
    }
    return nodes;
}

dijkstra_node_t *find_node_by_ptr(dijkstra_node_t **nodes, int count,
    node_t *ptr)
{
    int i = 0;

    while (i < count) {
        if (nodes[i]->node == ptr)
            return nodes[i];
        i++;
    }
    return NULL;
}

static bool is_valid_candidate(dijkstra_node_t *node)
{
    return !node->visited && node->dist != INF_DIST;
}

static bool is_better_candidate(dijkstra_node_t *current, dijkstra_node_t *min)
{
    return !min || current->dist < min->dist;
}

dijkstra_node_t *find_min_unvisited(dijkstra_node_t **nodes, int count)
{
    dijkstra_node_t *min = NULL;
    int i = 0;

    while (i < count) {
        if (is_valid_candidate(nodes[i]) && is_better_candidate(nodes[i], min))
            min = nodes[i];
        i++;
    }
    return min;
}
