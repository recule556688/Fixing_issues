/*
** EPITECH PROJECT, 2025
** robot_paths.c
** File description:
** Implementation of multi-robot pathfinding algorithm
*/

#include "../../include/algo.h"
#include <stdlib.h>

labyrinth_t *copy_labyrinth(labyrinth_t *original)
{
    labyrinth_t *copy = malloc(sizeof(labyrinth_t));
    node_t *current;
    node_t *new_current;
    node_t **node_mapping;
    int node_count = 0;
    int i = 0;

    if (!copy || !original)
        return NULL;
    
    // Count nodes
    current = original->root;
    while (current) {
        node_count++;
        current = current->next_node;
    }
    
    // Create mapping array
    node_mapping = malloc(sizeof(node_t *) * node_count * 2);
    if (!node_mapping) {
        free(copy);
        return NULL;
    }
    
    // Set initial values
    copy->robots = original->robots;
    copy->root = NULL;
    copy->tail = NULL;
    copy->start = NULL;
    copy->end = NULL;
    
    // Copy nodes and create mapping
    current = original->root;
    while (current) {
        new_current = make_room(copy, current->id, current->x, current->y);
        if (!new_current) {
            free_labyrinth(copy);
            free(node_mapping);
            return NULL;
        }
        
        // Store mapping of original to copy
        node_mapping[i*2] = current;
        node_mapping[i*2+1] = new_current;
        i++;
        
        // Set start/end if needed
        if (current == original->start)
            copy->start = new_current;
        if (current == original->end)
            copy->end = new_current;
            
        current = current->next_node;
    }
    
    // Copy edges using the mapping
    for (i = 0; i < node_count; i++) {
        current = node_mapping[i*2];
        edge_t *edge = current->root_edge;
        
        while (edge) {
            // Find target node in the mapping
            node_t *target = NULL;
            for (int j = 0; j < node_count; j++) {
                if (node_mapping[j*2] == edge->b) {
                    target = node_mapping[j*2+1];
                    break;
                }
            }
            
            if (target) {
                make_tunnel(copy, node_mapping[i*2+1]->id, target->id);
            }
            
            edge = edge->next_edge;
        }
    }
    
    free(node_mapping);
    return copy;
}

void remove_path_from_maze(labyrinth_t *maze, path_t *path)
{
    path_node_t *path_node;
    node_t *current;
    node_t *prev;

    if (!maze || !path || !path->head)
        return;
        
    // Skip start and end nodes
    path_node = path->head;
    if (path_node->room == maze->start)
        path_node = path_node->next;
        
    while (path_node && path_node->next) {
        if (path_node->next->room == maze->end) {
            path_node = path_node->next;
            continue;
        }
            
        // Remove node from maze
        current = maze->root;
        prev = NULL;
        
        while (current && current != path_node->room) {
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
        
        path_node = path_node->next;
    }
}

path_t **find_robot_paths(labyrinth_t *maze)
{
    path_t **paths;
    labyrinth_t *maze_copy;
    int i;
    node_t **node_mapping;
    int node_count = 0;
    node_t *current;

    if (!maze || maze->robots <= 0)
        return NULL;
        
    paths = malloc(sizeof(path_t *) * maze->robots);
    if (!paths)
        return NULL;

    // Count nodes for mapping
    current = maze->root;
    while (current) {
        node_count++;
        current = current->next_node;
    }

    // Create mapping array
    node_mapping = malloc(sizeof(node_t *) * node_count * 2);
    if (!node_mapping) {
        free(paths);
        return NULL;
    }
        
    for (i = 0; i < maze->robots; i++) {
        // Create a fresh copy of the maze for each robot
        maze_copy = copy_labyrinth(maze);
        if (!maze_copy) {
            // Free already allocated paths
            for (int j = 0; j < i; j++)
                free_path(paths[j]);
            free(paths);
            free(node_mapping);
            return NULL;
        }

        // Build node mapping
        current = maze->root;
        node_t *copy_current = maze_copy->root;
        int map_index = 0;
        while (current && copy_current) {
            node_mapping[map_index*2] = copy_current;
            node_mapping[map_index*2+1] = current;
            map_index++;
            current = current->next_node;
            copy_current = copy_current->next_node;
        }
        
        // Find shortest path for this robot
        path_t *temp_path = find_shortest_path(maze_copy, maze_copy->start, maze_copy->end);
        
        // If no path is found, we can't continue
        if (!temp_path) {
            free_labyrinth(maze_copy);
            for (int j = 0; j < i; j++)
                free_path(paths[j]);
            free(paths);
            free(node_mapping);
            return NULL;
        }

        // Map path back to original maze nodes
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

        path_node_t *current_node = temp_path->head;
        while (current_node) {
            node_t *original_node = NULL;
            for (int j = 0; j < node_count; j++) {
                if (node_mapping[j*2] == current_node->room) {
                    original_node = node_mapping[j*2+1];
                    break;
                }
            }
            if (original_node) {
                add_to_path(paths[i], original_node);
            }
            current_node = current_node->next;
        }

        // Reverse the path since add_to_path adds to the front
        reverse_path(paths[i]);
        
        // Free temporary path and maze copy
        free_path(temp_path);
        free_labyrinth(maze_copy);
    }

    free(node_mapping);
    return paths;
}

void simulate_robots(labyrinth_t *maze, path_t **paths)
{
    path_node_t **current_positions;
    bool *finished;
    bool all_finished;
    int step = 0;

    if (!maze || !paths) {
        my_putstr("Error: Invalid maze or paths\n");
        return;
    }

    // Initialize tracking arrays
    current_positions = malloc(sizeof(path_node_t *) * maze->robots);
    finished = malloc(sizeof(bool) * maze->robots);
    if (!current_positions || !finished) {
        free(current_positions);
        free(finished);
        my_putstr("Error: Memory allocation failed\n");
        return;
    }

    // Set initial positions
    for (int i = 0; i < maze->robots; i++) {
        current_positions[i] = paths[i] ? paths[i]->head : NULL;
        finished[i] = (current_positions[i] == NULL);
    }

    my_putstr("\nSimulating robot movements:\n");

    // Main simulation loop
    do {
        my_putstr("\nStep ");
        my_putnbr(step++);
        my_putstr(":\n");

        all_finished = true;
        // Try to move each robot
        for (int i = 0; i < maze->robots; i++) {
            if (finished[i])
                continue;

            if (!current_positions[i]) {
                finished[i] = true;
                continue;
            }

            // Check if robot can move to next position
            path_node_t *next = current_positions[i]->next;
            bool can_move = true;

            if (!next) {
                finished[i] = true;
                continue;
            }

            // Check for collisions with other robots' current positions
            for (int j = 0; j < maze->robots; j++) {
                if (i == j || finished[j] || !current_positions[j])
                    continue;

                if (current_positions[j]->room == next->room) {
                    can_move = false;
                    break;
                }
            }

            // Move robot if possible
            if (can_move) {
                my_putstr("Robot ");
                my_putnbr(i);
                my_putstr(" moves from ");
                if (current_positions[i] && current_positions[i]->room && current_positions[i]->room->id) {
                    my_putstr(current_positions[i]->room->id);
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

                current_positions[i] = next;
                if (!next->next) {
                    finished[i] = true;
                }
            }

            if (!finished[i]) {
                all_finished = false;
            }
        }
    } while (!all_finished);

    my_putstr("\nSimulation complete!\n");

    // Cleanup
    free(current_positions);
    free(finished);
}
