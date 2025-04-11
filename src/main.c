/*
** EPITECH PROJECT, 2025
** main
** File description:
** Main function for maze solver
*/

#include "../include/maze.h"
#include "../include/algo.h"
#include <stdlib.h>

static int handle_maze_parsing(labyrinth_t **maze)
{
    my_putstr("Starting maze parser\n");
    *maze = read_labyrinth();
    if (!*maze) {
        my_putstr("Error: Invalid maze format\n");
        return 84;
    }
    my_putstr("Parsed number of robots: ");
    my_putnbr((*maze)->robots);
    my_putstr("\n");
    my_putstr("\nMaze adjacency matrix:\n");
    print_labyrinth(*maze);
    if ((*maze)->robots <= 0) {
        my_putstr("Error: No robots specified\n");
        free_labyrinth(*maze);
        return 84;
    }
    return 0;
}

static int find_and_print_paths(labyrinth_t *maze, path_t ***robot_paths)
{
    my_putstr("\nNumber of robots: ");
    my_putnbr(maze->robots);
    my_putstr("\n\nFinding paths for robots...\n");
    *robot_paths = find_robot_paths(maze);
    if (!*robot_paths) {
        my_putstr("Error: Could not find paths for all robots\n");
        return 84;
    }
    my_putstr("\nFound paths for robots:\n");
    for (int i = 0; i < maze->robots; i++) {
        my_putstr("Robot ");
        my_putnbr(i);
        my_putstr(": ");
        if ((*robot_paths)[i]) {
            print_path((*robot_paths)[i]);
        } else {
            my_putstr("No path found!\n");
        }
    }
    return 0;
}

static void cleanup(labyrinth_t *maze, path_t **robot_paths)
{
    for (int i = 0; i < maze->robots; i++)
        free_path(robot_paths[i]);
    free(robot_paths);
    free_labyrinth(maze);
}

int main(void)
{
    labyrinth_t *maze;
    path_t **robot_paths;
    int ret = 0;

    if (handle_maze_parsing(&maze) != 0)
        return 84;
    if (find_and_print_paths(maze, &robot_paths) != 0) {
        free_labyrinth(maze);
        return 84;
    }
    my_putstr("\nSimulating robot movements...\n");
    simulate_robots(maze, robot_paths);
    cleanup(maze, robot_paths);
    return ret;
}
