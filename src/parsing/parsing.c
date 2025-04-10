/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-iuliia.dabizha
** File description:
** parsing
*/

#include "../include/maze.h"
#include <stdio.h>

static int parse_hashtag(char *buffer, labyrinth_t *maze, ROOM_PARSING_STATUS_t *room_status_flag)
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
static void print_room_coordinates(int x, int y){
    my_putstr("Room coordinates: X=");
    my_putnbr(x);
    my_putstr(", Y=");
    my_putnbr(y);
    my_putchar('\n');
}
static int parse_room_coordinates(int *x, int *y, char *current_token){
    current_token = detect_sep(current_token, ' ');
    if (!current_token) {
        my_putstr("Error: Missing X coordinate\n");
        return 84;
    }
    *x = my_atoi(current_token);
    current_token = detect_sep(current_token, ' ');
    if (!current_token) {
        my_putstr("Error: Missing Y coordinate\n");
        return 84;
    }
    *y = my_atoi(current_token);
    return 0;
}
static int parse_room(char *buffer, labyrinth_t *maze, ROOM_PARSING_STATUS_t room_status_flag){
    int x, y;
    node_t *new_room;

    my_putstr("Detected room: ");
    my_putstr(buffer);
    my_putchar('\n');

    if(parse_room_coordinates(&x, &y, buffer) == 84)
        return 84;
    print_room_coordinates(x, y);

    new_room = make_room(maze, buffer, x, y);
    if (!new_room)
        return 84;
    if (room_status_flag == START) {
        my_putstr("Set as start room\n");
        maze->start = new_room;
    } else if (room_status_flag == END) {
        my_putstr("Set as end room\n");
        maze->end = new_room;
    }
    return 0;
}
static int parse_tunnel(char *buffer, char *current_line, labyrinth_t *maze){
    if(!maze->end || !maze->start){
        my_putstr("GTFO - should not read tunnels before the starting/ending room has been read."); //DO something like this...
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
static int parse_room_or_tunnel(char *buffer, labyrinth_t *maze, ROOM_PARSING_STATUS_t room_status_flag)
{
    char *current_line = detect_sep(buffer, '-');

    if (current_line)
        return parse_tunnel(buffer, current_line, maze);
    else
        return parse_room(buffer, maze, room_status_flag);
}
static labyrinth_t *create_empty_labyrinth(void){
    labyrinth_t *maze = malloc(sizeof(labyrinth_t));
    if (!maze)
        return NULL;
    maze->root = NULL;
    maze->tail = NULL;
    maze->start = NULL;
    maze->end = NULL;
    return maze;
}

static void trim_line(char *line, ssize_t read){
    if (line[read - 1] == '\n')
        line[read - 1] = '\0';
}

static int init_labyrinth_with_num_robots(char *buffer, size_t *bufsize, labyrinth_t *maze){
    ssize_t read = getline(&buffer, bufsize, stdin);

    if (read == -1) {
        free(maze);
        return 0;
    }
    trim_line(buffer, read);
    maze->robots = my_atoi(buffer);
    return 1;
}

labyrinth_t *read_labyrinth(void)
{
    labyrinth_t *maze = create_empty_labyrinth();
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t read;
    ROOM_PARSING_STATUS_t room_status_flag = NONE;
    int ret;

    if (!maze || !init_labyrinth_with_num_robots(buffer, &bufsize, maze))
        return NULL;
    while ((read = getline(&buffer, &bufsize, stdin)) != -1) {
        //we've just read in a line.
        //Remove newline from end of line.
        trim_line(buffer, read);
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
