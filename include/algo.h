/*
** EPITECH PROJECT, 2025
** algo.h
** File description:
** Header file for pathfinding algorithms
*/

#ifndef ALGO_H_
    #define ALGO_H_

    #include "maze.h"
    #include <stdbool.h>

    #define INF_DIST 99999.0

    typedef struct path_node {
        node_t *room;
        struct path_node *next;
    } path_node_t;

    typedef struct path {
        path_node_t *head;
        int length;
    } path_t;

    /* Path operations */
    path_t *create_path(void);
    void add_to_path(path_t *path, node_t *room);
    void free_path(path_t *path);
    void print_path(path_t *path);
    /* Dijkstra algorithm */
    path_t *find_shortest_path(labyrinth_t *maze, node_t *start, node_t *end);
    /* Multi-robot pathfinding */
    path_t **find_robot_paths(labyrinth_t *maze);
    void simulate_robots(labyrinth_t *maze, path_t **paths);
    /* Helper functions */
    labyrinth_t *copy_labyrinth(labyrinth_t *original);
    void remove_path_from_maze(labyrinth_t *maze, path_t *path);
    void reverse_path(path_t *path);

#endif
