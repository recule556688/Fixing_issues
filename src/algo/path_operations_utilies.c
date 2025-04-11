/*
** EPITECH PROJECT, 2025
** Fixing_issues
** File description:
** path_operations_utilies
*/

#include "algo.h"
#include "struct.h"

int process_build_path(path_t *path, path_build_params_t *params)
{
    dijkstra_node_t *current;
    node_t *node = params->end;

    while (node && node != params->start) {
        add_to_path(path, node);
        current = find_node_by_ptr(params->nodes, params->count, node);
        if (!current)
            return 0;
        node = current->prev;
    }
    if (node == params->start) {
        add_to_path(path, params->start);
        return 1;
    }
    return 0;
}

path_t *build_path(dijkstra_node_t **nodes, int count, node_t *start,
    node_t *end)
{
    path_t *path = create_path();
    dijkstra_node_t *current;
    path_build_params_t params = {nodes, count, start, end};

    if (!path)
        return NULL;
    current = find_node_by_ptr(nodes, count, end);
    if (!current || current->dist == INF_DIST) {
        free_path(path);
        return NULL;
    }
    if (!process_build_path(path, &params)) {
        free_path(path);
        return NULL;
    }
    return path;
}
