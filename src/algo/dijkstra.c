/*
** EPITECH PROJECT, 2025
** dijkstra.c
** File description:
** Implementation of Dijkstra's algorithm for pathfinding
*/

#include "../../include/struct.h"
#include "../../include/algo.h"
#include <stdlib.h>
#include <float.h>

static dijkstra_node_t *find_min_distance_node(dijkstra_node_t **nodes, int count)
{
    dijkstra_node_t *min_node = NULL;
    float min_dist = FLT_MAX;

    for (int i = 0; i < count; i++) {
        if (!nodes[i]->visited && nodes[i]->dist < min_dist) {
            min_dist = nodes[i]->dist;
            min_node = nodes[i];
        }
    }
    return min_node;
}

static int count_nodes(labyrinth_t *maze)
{
    int count = 0;
    node_t *current = maze->root;

    while (current) {
        count++;
        current = current->next_node;
    }
    return count;
}

static dijkstra_node_t **initialize_nodes(labyrinth_t *maze, node_t *start)
{
    int count = count_nodes(maze);
    dijkstra_node_t **nodes = malloc(sizeof(dijkstra_node_t *) * count);
    node_t *current = maze->root;
    int i = 0;

    if (!nodes)
        return NULL;
    while (current) {
        nodes[i] = malloc(sizeof(dijkstra_node_t));
        if (!nodes[i]) {
            for (int j = 0; j < i; j++)
                free(nodes[j]);
            free(nodes);
            return NULL;
        }
        nodes[i]->node = current;
        nodes[i]->dist = (current == start) ? 0 : INF_DIST;
        nodes[i]->prev = NULL;
        nodes[i]->visited = false;
        current = current->next_node;
        i++;
    }
    return nodes;
}

static dijkstra_node_t *find_node_by_ptr(dijkstra_node_t **nodes,
    int count, node_t *ptr)
{
    if (!nodes || !ptr)
        return NULL;
    for (int i = 0; i < count; i++) {
        if (nodes[i] && nodes[i]->node == ptr)
            return nodes[i];
    }
    return NULL;
}

void reverse_path(path_t *path)
{
    path_node_t *prev = NULL;
    path_node_t *current = path->head;
    path_node_t *next;

    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    path->head = prev;
}

static path_t *build_path(dijkstra_node_t **nodes, int count,
    node_t *start, node_t *end)
{
    path_t *path = create_path();
    dijkstra_node_t *current;

    if (!path)
        return NULL;

    current = find_node_by_ptr(nodes, count, end);
    if (!current || current->dist == INF_DIST) {
        free_path(path);
        return NULL;
    }
    while (current && current->node) {
        path_node_t *new_node = malloc(sizeof(path_node_t));
        if (!new_node) {
            free_path(path);
            return NULL;
        }
        new_node->room = current->node;
        new_node->next = path->head;
        path->head = new_node;
        path->length++;
        if (current->node == start)
            break;
        current = find_node_by_ptr(nodes, count, current->prev);
    }
    if (!current || current->node != start) {
        free_path(path);
        return NULL;
    }
    return path;
}

static void free_dijkstra_nodes(dijkstra_node_t **nodes, int count)
{
    if (!nodes)
        return;
    for (int i = 0; i < count; i++)
        free(nodes[i]);
    free(nodes);
}

path_t *find_shortest_path(labyrinth_t *maze, node_t *start, node_t *end)
{
    int node_count;
    dijkstra_node_t **nodes;
    dijkstra_node_t *current;
    path_t *path = NULL;

    if (!maze || !start || !end)
        return NULL;

    node_count = count_nodes(maze);
    nodes = initialize_nodes(maze, start);
    if (!nodes)
        return NULL;
    while ((current = find_min_distance_node(nodes, node_count))) {
        current->visited = true;
        edge_t *edge = current->node->root_edge;
        while (edge) {
            dijkstra_node_t *neighbor = find_node_by_ptr(nodes, node_count, edge->b);
            if (neighbor && !neighbor->visited) {
                float new_dist = current->dist + edge->length;
                if (new_dist < neighbor->dist) {
                    neighbor->dist = new_dist;
                    neighbor->prev = current->node;
                }
            }
            edge = edge->next_edge;
        }
    }
    path = build_path(nodes, node_count, start, end);
    free_dijkstra_nodes(nodes, node_count);
    return path;
}

path_t *create_path(void)
{
    path_t *path = malloc(sizeof(path_t));

    if (!path)
        return NULL;
    path->head = NULL;
    path->length = 0;
    return path;
}

void add_to_path(path_t *path, node_t *room)
{
    path_node_t *new_node;

    if (!path || !room)
        return;
    new_node = malloc(sizeof(path_node_t));
    if (!new_node)
        return;
    new_node->room = room;
    new_node->next = path->head;
    path->head = new_node;
    path->length++;
}

void free_path(path_t *path)
{
    if (!path)
        return;
    path_node_t *current = path->head;
    while (current) {
        path_node_t *next = current->next;
        free(current);
        current = next;
    }
    free(path);
}

void print_path(path_t *path)
{
    if (!path || !path->head) {
        my_putstr("Empty path\n");
        return;
    }
    my_putstr("Path: ");
    path_node_t *current = path->head;
    while (current) {
        if (current->room && current->room->id) {
            my_putstr(current->room->id);
            if (current->next)
                my_putstr(" -> ");
        }
        current = current->next;
    }
    my_putchar('\n');
}
