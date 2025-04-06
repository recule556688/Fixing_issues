/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-iuliia.dabizha
** File description:
** parsing
*/

#include "../include/my.h"

char *detect_sep(char *str, char sep)
{
    char *c = str;

    while (*c) {
        if (*c == sep) {
            *c = 0;
            ++c;
            return c;
        }
        ++c;
    }
    return NULL;
}

node_t *find_room(labyrinth_t *rs, char *id)
{
    node_t *t = rs->root;

    while (t) {
        if (my_strcmp(t->id, id) == 0) {
            break;
        }
        ++t;
    }
    return t;
}

float my_sqrt(float nb)
{
    float t = nb / 2.0f;
    float eps = 0.00001f;
    float t2 = t * t;

    if (nb < 0) {
        return -1;
    }
    while ((t2 - nb) > eps || (nb - t2) > eps) {
        t = (t + nb / t) / 2.0f;
        t2 = t * t;
    }
    return t;
}

void add_edge(node_t *r, edge_t *c)
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
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float d = my_sqrt(dx * dx + dy * dy);
    edge_t *e1 = (edge_t *)malloc(sizeof(edge_t *));
    edge_t *e2 = (edge_t *)malloc(sizeof(edge_t *));

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

void make_room(labyrinth_t *res, char *id, int x, int y)
{
    node_t *room = (node_t *)malloc(sizeof(node_t *));
    int n = my_strlen(id);

    room->id = (char *)malloc(n + 1);
    my_stcpy(room->id, id);
    room->x = x;
    room->y = y;
    room->root_edge = NULL;
    if (res->tail) {
        res->tail->next_node = room;
    } else {
        res->root = room;
    }
    res->tail = room;
}

void parse_room_or_tunnel(char *buffer, labyrinth_t *res, int room_status_flag)
{
    char *b = detect_sep(buffer, '-');
    int x;
    int y;

    if (b) {
        x = my_atoi(buffer);
        y = my_atoi(b);
        make_tunnel(res, x, y);
    } else {
        b = detect_sep(buffer, ' ');
        if (!b)
            return;
        x = my_atoi(b);
        b = detect_sep(b, ' ');
        if (!b)
            return;
        y = my_atoi(b);
        make_room(res, buffer, x, y);
    }
}

void parse_hashtag(char *buffer, labyrinth_t *res, int *room_status_flag)
{
    if (buffer[1] != '#') {
        return;
    }
    if (my_strcmp(buffer + 2, "start") == 0) {
        *room_status_flag = 1;
    } else if (my_strcpm(buffer + 2, "end") == 0) {
        *room_status_flag = -1;
    }
}

labyrinth_t *read_labyrinth(void)
{
    labyrinth_t *res = (labyrinth_t *)malloc(sizeof(labyrinth_t *));
    node_t *nd;
    edge_t *s;
    char buffer[MAX_BUFFER];
    int n = MAX_BUFFER;
    int room_status_flag = 0;

    res->root = NULL;
    res->tail = NULL;
    getline(&buffer, &n, stdin);
    res->robots = my_atoi(buffer);
    while (getline(&buffer, &n, stdin)) {
        if (buffer[0] != '#') {
            parse_room_or_tunnel(buffer, res, room_status_flag);
        } else {
            parse_hashtag(buffer, res, &room_status_flag);
        }
    }
    return res;
}
