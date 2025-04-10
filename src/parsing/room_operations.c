/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-iuliia.dabizha
** File description:
** Room operations
*/

#include "../../include/maze.h"

node_t *find_room(labyrinth_t *rs, char *id)
{
    node_t *current = rs->root;

    while (current) {
        if (my_strcmp(current->id, id) == 0)
            return current;
        current = current->next_node;
    }
    return NULL;
}

static void add_edge(node_t *r, edge_t *c)
{
    edge_t *e0 = NULL;
    edge_t *e = r->root_edge;

    if (!e) {
        r->root_edge = c;
        return;
    }
    while (e) {
        e0 = e;
        e = e->next_edge;
    }
    e0->next_edge = c;
}

static edge_t *create_and_add_tunnel(node_t *a, node_t *b, float dist)
{
    edge_t *e = malloc(sizeof(edge_t));

    if (!e){
        return NULL;
    }
    e->a = a;
    e->b = b;
    e->length = dist;
    e->next_edge = NULL;
    add_edge(a, e);
    return e;
}

int make_tunnel(labyrinth_t *res, char *x, char *y)
{
    node_t *a = find_room(res, x);
    node_t *b = find_room(res, y);
    float dx = 0;
    float dy = 0;
    float d = 0;

    if (!a || !b)
        return 84;
    dx = b->x - a->x;
    dy = b->y - a->y;
    d = my_sqrt(dx * dx + dy * dy);
    if (!create_and_add_tunnel(a, b, d) || !create_and_add_tunnel(b, a, d))
        return 84;
    return 0;
}

static void add_room_to_labyrinth(labyrinth_t *maze, node_t *room)
{
    room->root_edge = NULL;
    room->next_node = NULL;
    if (maze->tail)
        maze->tail->next_node = room;
    else
        maze->root = room;
    maze->tail = room;
}

node_t *clone_room(labyrinth_t *new_maze, labyrinth_t *old_maze, 
    node_t *orig)
{
    node_t *new_room = make_room(new_maze, orig->id, orig->x, orig->y);
    if (orig == old_maze->start)
        new_maze->start = new_room;
    if (orig == old_maze->end)
        new_maze->end = new_room;
    return new_room;
}
node_t *make_room(labyrinth_t *res, char *id, int x, int y)
{
    node_t *room = malloc(sizeof(node_t));

    if (!room)
        return NULL;
    room->id = my_strdup(id);
    if (!room->id) {
        free(room);
        my_putstr("Error: Failed to create room\n");
        return NULL;
    }
    room->x = x;
    room->y = y;
    add_room_to_labyrinth(res, room);
    return room;
}
