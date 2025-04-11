/*
** EPITECH PROJECT, 2025
** robot_paths.c
** File description:
** Implementation of multi-robot pathfinding algorithm
*/

#include "../../include/algo.h"
#include <stdlib.h>

static int num_labyrinth_nodes(labyrinth_t *maze)
{
    node_t *current = maze->root;
    int node_count = 0;

    while (current) {
        node_count++;
        current = current->next_node;
    }
    return node_count;
}

node_t **copy_labyrinth_nodes(labyrinth_t *copy,
    labyrinth_t *original, int *node_count)
{
    node_t *current;
    node_t *new_current;
    node_t **node_mapping;
    int i = 0;

    *node_count = num_labyrinth_nodes(original);
    node_mapping = malloc(sizeof(node_t *) * (*node_count) * 2);
    if (!node_mapping)
        return NULL;
    current = original->root;
    while (current) {
        new_current = clone_room(copy, original, current);
        if (!new_current) {
            free(node_mapping);
            return NULL;
        }
        node_mapping[i * 2] = current;
        node_mapping[i * 2 + 1] = new_current;
        i++;
        current = current->next_node;
    }
    return node_mapping;
}

void copy_labyrinth_edges(labyrinth_t *copy, node_t **node_mapping,
    int node_count)
{
    node_t *current;
    edge_t *edge;
    node_t *target;

    for (int i = 0; i < node_count; i++) {
        current = node_mapping[i * 2];
        edge = current->root_edge;
        while (edge) {
            target = NULL;
            for (int j = 0; j < node_count; j++) {
                if (node_mapping[j * 2] == edge->b) {
                    target = node_mapping[j * 2 + 1];
                    break;
                }
            }
            if (target)
                make_tunnel(copy, node_mapping[i * 2 + 1]->id, target->id);
            edge = edge->next_edge;
        }
    }
}

labyrinth_t *copy_labyrinth(labyrinth_t *original)
{
    labyrinth_t *copy = create_empty_labyrinth();
    node_t **node_mapping;
    int node_count;

    if (!copy || !original)
        return NULL;
    node_mapping = copy_labyrinth_nodes(copy, original, &node_count);
    if (!node_mapping) {
        free(copy);
        return NULL;
    }
    copy->robots = original->robots;
    copy_labyrinth_edges(copy, node_mapping, node_count);
    free(node_mapping);
    return copy;
}

void remove_node_from_maze(labyrinth_t *maze, node_t *room)
{
    node_t *current = maze->root;
    node_t *prev = NULL;

    while (current && current != room) {
        prev = current;
        current = current->next_node;
    }
    if (current) {
        if (prev)
            prev->next_node = current->next_node;
        else
            maze->root = current->next_node;
        if (current == maze->tail)
            maze->tail = prev;
    }
}

void remove_path_from_maze(labyrinth_t *maze, path_t *path)
{
    path_node_t *path_node;

    if (!maze || !path || !path->head)
        return;
    path_node = path->head;
    if (path_node->room == maze->start)
        path_node = path_node->next;
    while (path_node && path_node->next) {
        if (path_node->next->room == maze->end) {
            path_node = path_node->next;
            continue;
        }
        remove_node_from_maze(maze, path_node->room);
        path_node = path_node->next;
    }
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

void print_robot_movement(int robot_index, path_node_t *current, path_node_t *next)
{
    my_putstr("Robot ");
    my_putnbr(robot_index);
    my_putstr(" moves from ");
    if (current && current->room && current->room->id) {
        my_putstr(current->room->id);
    } else {
        my_putstr("(unknown)");
    }
    my_putstr(" to ");
    if (next && next->room && next->room->id) {
        my_putstr(next->room->id);
    } else {
        my_putstr("(unknown)");
    }
    my_putstr("\n");
}

bool process_robot_movement(int robot_index, labyrinth_t *maze,
    path_node_t **current_positions, bool *finished)
{
    path_node_t *next = current_positions[robot_index]->next;
    bool can_move = true;

    if (!next) {
        finished[robot_index] = true;
        return false;
    }
    for (int j = 0; j < maze->robots; j++) {
        if (robot_index == j || finished[j] || !current_positions[j])
            continue;
        if (current_positions[j]->room == next->room) {
            can_move = false;
            break;
        }
    }
    if (can_move) {
        print_robot_movement(robot_index, current_positions[robot_index], next);
        current_positions[robot_index] = next;
        if (!next->next) {
            finished[robot_index] = true;
        }
    }
    return !finished[robot_index];
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

    if (!initialize_simulation(maze, paths, &current_positions, &finished))
        return;
    do {
        all_finished = simulate_step(maze, current_positions, finished, step++);
    } while (!all_finished);
    my_putstr("\nSimulation complete!\n");
    free(current_positions);
    free(finished);
}
