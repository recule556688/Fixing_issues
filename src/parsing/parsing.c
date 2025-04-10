/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-iuliia.dabizha
** File description:
** parsing
*/

#include "../include/maze.h"
#include <stdio.h>

static int parse_hashtag(char *buffer, labyrinth_t *maze, ROOM_PARSING_STATUS *room_status_flag)
{
    my_putstr("Parsing hashtag: ");
    my_putstr(buffer);
    my_putchar('\n');
    if(*room_status_flag != NONE){
        my_putstr("Error: Already parsing start or end room.\n");
        return 84;
    }

    if (buffer[1] != '#') {
        my_putstr("Regular comment, ignoring\n");
        return 0; /* Regular comment, ignore */
    }
    if (my_strcmp(buffer + 2, "start") == 0) {
        my_putstr("Found ##start command\n");
        //You're checking if either ##start already appeared on the previous line, or maze->start already defined.

        if (maze->start) {
            my_putstr("Error: Start room already defined\n");
            return 84;
        }
        *room_status_flag = START;
    } else if (my_strcmp(buffer + 2, "end") == 0) {
        my_putstr("Found ##end command\n");
        if (maze->end) {
            my_putstr("Error: End room already defined\n");
            return 84;
        }
        *room_status_flag = END;
    } else {
        my_putstr("Unknown ## command: ");
        my_putstr(buffer + 2);
        my_putchar('\n');
    }
    
    return 0;
}

static int parse_room_or_tunnel(char *buffer, labyrinth_t *maze, ROOM_PARSING_STATUS room_status_flag)
{
    char *current_line = detect_sep(buffer, '-');
    int x, y;
    node_t *new_room;

    if (current_line) {
        if(!maze->end){
            my_putstr("GTFO - should not read tunnels before the ending room has been read."); //DO something like this...
            return 84;
        }
        my_putstr("Detected tunnel: ");
        my_putstr(buffer);
        my_putstr(" to ");
        my_putstr(current_line);
        my_putchar('\n');

        make_tunnel(maze, buffer, current_line);
        return 0;
    }
    else{
        // if(maze->end){
        //     my_putstr("GTFO - should not read rooms after the ending room has been read."); //Do something like this...
        //     return 84;
        // }
        my_putstr("Detected room: ");
        my_putstr(buffer);
        my_putchar('\n');

        current_line = detect_sep(buffer, ' ');
        if (!current_line) {
            my_putstr("Error: Missing X coordinate\n");
            return 84;
        }
        x = my_atoi(current_line);
        current_line = detect_sep(current_line, ' ');
        if (!current_line) {
            my_putstr("Error: Missing Y coordinate\n");
            return 84;
        }
        y = my_atoi(current_line);
        my_putstr("Room coordinates: X=");
        my_putchar('0' + x);
        my_putstr(", Y=");
        my_putchar('0' + y);
        my_putchar('\n');
        new_room = make_room(maze, buffer, x, y);
        if (!new_room) {
            my_putstr("Error: Failed to create room\n");
            return 84;
        }
        if (room_status_flag == START) {
            my_putstr("Set as start room\n");
            maze->start = new_room;
        } else if (room_status_flag == END) {
            my_putstr("Set as end room\n");
            maze->end = new_room;
        }
    }
    return 0;
}
labyrinth_t *read_labyrinth(void)
{
    labyrinth_t *maze = malloc(sizeof(labyrinth_t));
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t read;
    ROOM_PARSING_STATUS room_status_flag = NONE;
    int ret;

    if (!maze)
        return NULL;
    maze->root = NULL;
    maze->tail = NULL;
    maze->start = NULL;
    maze->end = NULL;

    read = getline(&buffer, &bufsize, stdin);
    if (read == -1) {
        free(maze);
        return NULL;
    }

    if (buffer[read - 1] == '\n')
        buffer[read - 1] = '\0';

    maze->robots = my_atoi(buffer);

    while ((read = getline(&buffer, &bufsize, stdin)) != -1) {
        //we've just read in a line.
        //Remove newline from end of line.
        if (buffer[read - 1] == '\n')
            buffer[read - 1] = '\0';

        if (buffer[0] == '#') { //we're about to read something important...
            ret = parse_hashtag(buffer, maze, &room_status_flag);
        } else {
            ret = parse_room_or_tunnel(buffer, maze, room_status_flag);
            /* Only reset room_status_flag after we've used it for a room */
            room_status_flag = NONE;
        }

        if (ret == 84) {
            free_labyrinth(maze);
            free(buffer);
            return NULL;
        }
    }
    free(buffer);

    if (!maze->start || !maze->end) {
        free_labyrinth(maze);
        return NULL;
    }

    return maze;
}
