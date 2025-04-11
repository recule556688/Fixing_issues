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


static int init_processing_data(labyrinth_t *maze, processing_data_t *data){
    if(maze->robots <= 0){
        return 0;
    }
    data->paths = malloc(sizeof(path_t *) * maze->robots);
    if (!data->paths)
        return 0;
    data->current = maze->root;
    while (data->current) {
        data->node_count++;
        data->current = data->current->next_node;
    }
    data->node_mapping = malloc(sizeof(node_t *) * data->node_count * 2);
    if (!data->node_mapping) {
        free(data->paths);
        return 0;
    }
    return 1;
}

static path_t *init_empty_path(processing_data_t *data, int i){
    path_t *newPath= create_path();
    int j;
    
    if(!newPath){
        free_path(data->temp_path);
        free_labyrinth(data->maze_copy);
        for (j = 0; j < i; j++)
            free_path(data->paths[j]);
        free(data->paths);
        free(data->node_mapping);
        return NULL;
    }
    return newPath;
}

int update_processing_data(processing_data_t *data, labyrinth_t *maze, int i){
    data->maze_copy = copy_labyrinth(maze);
    if (!data->maze_copy) {
        for (int j = 0; j < i; j++)
            free_path(data->paths[j]);
        free(data->paths);
        free(data->node_mapping);
        return 0;
    }
    data->current = maze->root;
    data->copy_current = data->maze_copy->root;
    data->map_index = 0;
    while (data->current && data->copy_current) {
        data->node_mapping[data->map_index * 2] = data->copy_current;
        data->node_mapping[data->map_index * 2 + 1] = data->current;
        data->map_index++;
        data->current = data->current->next_node;
        data->copy_current = data->copy_current->next_node;
    }
    return 1;
}

static int advance_processing_data(processing_data_t *data, 
    labyrinth_t *maze_copy, int i)
{
    data->temp_path = find_shortest_path(maze_copy, maze_copy->start, 
        maze_copy->end);
    if (!data->temp_path) {
        free_labyrinth(data->maze_copy);
        for (int j = 0; j < i; j++)
            free_path(data->paths[j]);
        free(data->paths);
        free(data->node_mapping);
        return 0;
    }
    data->paths[i] = init_empty_path(data, i);
    if (!data->paths[i])
        return 0;
    data->current_node = data->temp_path->head;
    return 1;
}

static void fix_processing_data(processing_data_t *data, int i){
    data->current_node = data->temp_path->head;
    while (data->current_node) {
        data->original_node = NULL;
        for (int j = 0; j < data->node_count; j++) {
            if (data->node_mapping[j * 2] == data->current_node->room) {
                data->original_node = data->node_mapping[j * 2 + 1];
                break;
            }
        }
        if (data->original_node)
            add_to_path(data->paths[i], data->original_node);
        data->current_node = data->current_node->next;
    }
    reverse_path(data->paths[i]);
    free_path(data->temp_path);
    free_labyrinth(data->maze_copy);
}


path_t **find_robot_paths(labyrinth_t *maze)
{
    processing_data_t data;
    int i;
    if (!maze || !init_processing_data(maze, &data))
        return NULL;
    for (i = 0; i < maze->robots; i++) {
        if(!update_processing_data(&data, maze, i))
            return NULL;
        if(!advance_processing_data(&data, data.maze_copy, i))
            return NULL;
        fix_processing_data(&data, i);
    }
    free(data.node_mapping);
    return data.paths;
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
