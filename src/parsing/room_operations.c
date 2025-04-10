/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-iuliia.dabizha
** File description:
** Room operations
*/

#include "../include/maze.h"

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

void make_tunnel(labyrinth_t *res, char *x, char *y)
{
    node_t *a = find_room(res, x);
    node_t *b = find_room(res, y);
    edge_t *e1 = malloc(sizeof(edge_t));
    edge_t *e2 = malloc(sizeof(edge_t));
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float d = my_sqrt(dx * dx + dy * dy);

    if (!a || !b || !e1 || !e2)
        return;
    e1->a = a;
    e1->b = b;
    e1->length = d;
    e1->next_edge = NULL;
    e2->a = b;
    e2->b = a;
    e2->length = d;
    e2->next_edge = NULL;
    add_edge(a, e1);
    add_edge(b, e2);
}

node_t *make_room(labyrinth_t *res, char *id, int x, int y)
{
    node_t *room = malloc(sizeof(node_t));

    if (!room)
        return NULL;
    room->id = my_strdup(id);
    if (!room->id) {
        free(room);
        return NULL;
    }
    room->x = x;
    room->y = y;
    room->root_edge = NULL;
    room->next_node = NULL;
    if (res->tail) {
        res->tail->next_node = room;
    } else {
        res->root = room;
    }
    res->tail = room;
    return room;
}
