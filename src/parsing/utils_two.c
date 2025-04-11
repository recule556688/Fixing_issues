/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-iuliia.dabizha
** File description:
** utils_two
*/

#include "../../include/maze.h"
#include <stdio.h>

void handle_unknown_command(const char *buffer)
{
    my_putstr("Unknown ## command: ");
    my_putstr(buffer + 2);
    my_putchar('\n');
}

void print_room_coordinates(int x, int y)
{
    my_putstr("Room coordinates: X=");
    my_putnbr(x);
    my_putstr(", Y=");
    my_putnbr(y);
    my_putchar('\n');
}

void log_detected_room(const char *buffer)
{
    my_putstr("Detected room: ");
    my_putstr(buffer);
    my_putchar('\n');
}

void trim_line(char *line, ssize_t read)
{
    if (line[read - 1] == '\n')
        line[read - 1] = '\0';
}
