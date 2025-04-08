/*
** EPITECH PROJECT, 2025
** main
** File description:
** Main function for maze solver
*/

#include "../include/maze.h"
#include <stdlib.h>

int main(void)
{
    labyrinth_t *maze;
    
    my_putstr("Starting maze parser\n");
    maze = read_labyrinth();

    if (!maze) {
        my_putstr("Error: Invalid maze format\n");
        return 84;
    }
    
    my_putstr("\nMaze adjacency matrix:\n");
    print_labyrinth(maze);
    free_labyrinth(maze);
    return 0;
}