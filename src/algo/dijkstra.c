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

static dijkstra_node_t *find_min_distance_node(dijkstra_node_t **nodes,
    int count)
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

static void update_neighbor_distance(dijkstra_node_t *current,
    dijkstra_node_t *neighbor, float new_dist)
{
    if (new_dist < neighbor->dist) {
        neighbor->dist = new_dist;
        neighbor->prev = current->node;
    }
}

static void update_neighbor_distances(dijkstra_node_t *current,
    dijkstra_node_t **nodes, int node_count)
{
    edge_t *edge = current->node->root_edge;
    dijkstra_node_t *neighbor;
    float new_dist;

    while (edge) {
        neighbor = find_node_by_ptr(nodes, node_count, edge->b);
        if (neighbor && !neighbor->visited) {
            new_dist = current->dist + edge->length;
            update_neighbor_distance(current, neighbor, new_dist);
        }
        edge = edge->next_edge;
    }
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
    current = find_min_distance_node(nodes, node_count);
    while (current) {
        current->visited = true;
        update_neighbor_distances(current, nodes, node_count);
        current = find_min_distance_node(nodes, node_count);
    }
    path = build_path(nodes, node_count, start, end);
    free_nodes_array(nodes, node_count);
    return path;
}
