/*
** EPITECH PROJECT, 2025
** robot_paths.c
** File description:
** Implementation of multi-robot pathfinding algorithm
*/

#include "../../include/algo.h"
#include <stdlib.h>

bool copy_nodes_to_mapping(labyrinth_t *copy, labyrinth_t *original,
    node_t **node_mapping, int node_count)
{
    node_t *current = original->root;
    node_t *new_current;
    int i = 0;

    while (current) {
        new_current = clone_room(copy, original, current);
        if (!new_current) {
            free(node_mapping);
            return false;
        }
        node_mapping[i * 2] = current;
        node_mapping[i * 2 + 1] = new_current;
        i++;
        current = current->next_node;
    }
    return true;
}

path_t **find_robot_paths(labyrinth_t *maze)
{
    path_t **paths;
    labyrinth_t *maze_copy;
    int i;
    int node_count = 0;
    node_t **node_mapping;
    node_t *current;
    node_t *copy_current;
    path_t *temp_path;
    int map_index;
    path_node_t *current_node;
    node_t *original_node;

    if (!maze || maze->robots <= 0)
        return NULL;
    paths = malloc(sizeof(path_t *) * maze->robots);
    if (!paths)
        return NULL;
    current = maze->root;
    while (current) {
        node_count++;
        current = current->next_node;
    }
    node_mapping = malloc(sizeof(node_t *) * node_count * 2);
    if (!node_mapping) {
        free(paths);
        return NULL;
    }
    for (i = 0; i < maze->robots; i++) {
        maze_copy = copy_labyrinth(maze);
        if (!maze_copy) {
            for (int j = 0; j < i; j++)
                free_path(paths[j]);
            free(paths);
            free(node_mapping);
            return NULL;
        }
        current = maze->root;
        copy_current = maze_copy->root;
        map_index = 0;
        while (current && copy_current) {
            node_mapping[map_index * 2] = copy_current;
            node_mapping[map_index * 2 + 1] = current;
            map_index++;
            current = current->next_node;
            copy_current = copy_current->next_node;
        }
        temp_path = find_shortest_path(maze_copy, maze_copy->start, maze_copy->end);
        if (!temp_path) {
            free_labyrinth(maze_copy);
            for (int j = 0; j < i; j++)
                free_path(paths[j]);
            free(paths);
            free(node_mapping);
            return NULL;
        }
        paths[i] = create_path();
        if (!paths[i]) {
            free_path(temp_path);
            free_labyrinth(maze_copy);
            for (int j = 0; j < i; j++)
                free_path(paths[j]);
            free(paths);
            free(node_mapping);
            return NULL;
        }
        current_node = temp_path->head;
        while (current_node) {
            original_node = NULL;
            for (int j = 0; j < node_count; j++) {
                if (node_mapping[j * 2] == current_node->room) {
                    original_node = node_mapping[j * 2 + 1];
                    break;
                }
            }
            if (original_node)
                add_to_path(paths[i], original_node);
            current_node = current_node->next;
        }
        reverse_path(paths[i]);
        free_path(temp_path);
        free_labyrinth(maze_copy);
    }
    free(node_mapping);
    return paths;
}

bool initialize_simulation(labyrinth_t *maze, path_t **paths,
    path_node_t ***current_positions, bool **finished)
{
    if (!maze || !paths) {
        my_putstr("Error: Invalid maze or paths\n");
        return false;
    }
    *current_positions = malloc(sizeof(path_node_t *) * maze->robots);
    *finished = malloc(sizeof(bool) * maze->robots);
    if (!*current_positions || !*finished) {
        free(*current_positions);
        free(*finished);
        my_putstr("Error: Memory allocation failed\n");
        return false;
    }
    for (int i = 0; i < maze->robots; i++) {
        (*current_positions)[i] = paths[i] ? paths[i]->head : NULL;
        (*finished)[i] = ((*current_positions)[i] == NULL);
    }
    my_putstr("\nSimulating robot movements:\n");
    return true;
}

bool simulate_step(labyrinth_t *maze, path_node_t **current_positions,
    bool *finished, int step)
{
    bool all_finished = true;

    my_putstr("\nStep ");
    my_putnbr(step);
    my_putstr(":\n");
    for (int i = 0; i < maze->robots; i++) {
        if (finished[i])
            continue;
        if (!current_positions[i]) {
            finished[i] = true;
            continue;
        }
        if (process_robot_movement(i, maze, current_positions, finished)) {
            all_finished = false;
        }
    }
    return all_finished;
}

void simulate_robots(labyrinth_t *maze, path_t **paths)
{
    path_node_t **current_positions;
    bool *finished;
    int step = 0;
    bool all_finished;
    int step_incremented;

    if (!initialize_simulation(maze, paths, &current_positions, &finished))
        return;
    do {
        step_incremented = step;
        step++;
        all_finished =
            simulate_step(maze, current_positions, finished, step_incremented);
    } while (!all_finished);
    my_putstr("\nSimulation complete!\n");
    free(current_positions);
    free(finished);
}
