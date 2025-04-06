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

//O(n) lookup, but this isn't terrible.
//Bonus: make BST for lookups to make this more efficient haha O(log(n)) lookup
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

//TODO: fix something if 
void parse_room_or_tunnel(char *buffer, labyrinth_t *res, int room_status_flag)
{
    char *b = detect_sep(buffer, '-');
    int x;
    int y;
    //update start/end pointer based on room_status_flag
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
        return; //We're just reading a comment
    }
    if (my_strcmp(buffer + 2, "start") == 0) {
        *room_status_flag = 1; //WHAT IF START HAS ALREADY APPEARED?
    } else if (my_strcpm(buffer + 2, "end") == 0) {
        *room_status_flag = -1; //WHAT IF END HAS ALREADY APPEARED?
    }

    //Handle these cases, have a different status flag if room_status_flag already 1/-1 or if start/end room already defined

    //store the start/end room in the struct for labyrinth/maze? this makes returning an error easier...


    //check more things. maybe to make it easier we can add pointers to them in the struct.
    //And use a nullcheck to verify for them.
    //Also we want handle cases like this:
    //##start
    //##start
    //or 
    //##start
    //#haha 
}

labyrinth_t *read_labyrinth(void)
{
    labyrinth_t *res = (labyrinth_t *)malloc(sizeof(labyrinth_t *));
    //node_t *nd;
    //edge_t *s;
    char buffer[MAX_BUFFER];
    int n = MAX_BUFFER;
    int room_status_flag = 0; //Used to tell us if we're going to read the start/end...

    res->root = NULL;
    res->tail = NULL;

    //Read the number of robots
    getline(&buffer, &n, stdin);
    res->robots = my_atoi(buffer);


    //Steps: 

    //Read in all rooms with their coordinates....
    //For each room and each edge/tunnel, create an edge for both ends of the tunnel/edge.
    //Add a copy of the edge to both linked lists. 
    //While not the best design, this will make the adjacency matrix printing easier.


    //Read rooms and tunnels, or potentially ##start/##next.
    // 

    //If bad room_status_flag, stop...
    while (getline(&buffer, &n, stdin)) {
        if (buffer[0] != '#') {
            parse_room_or_tunnel(buffer, res, room_status_flag);
        } else {
            parse_hashtag(buffer, res, &room_status_flag);
        }
    }
    return res;
}
void free_labyrinth(labyrinth_t *maze){
    //TODO other stuff to free it...
    free(maze);
}
void print_labyrinth(labyrinth_t *maze){
    //Print the adjacency matrix of the graph!
    //print a line with the names of all nodes (go through the list...)
    //then, for each node, print a single line, with the name of the node and the distance to each node adjacent to it.

    //Example: 
    
    //Start (0,0) - A (1,0) - End  (2,0)
    

    //       Start  A   End
    // Start -    1.0   -  
    // A     1.0   -    1.0
    // End   -    1.0    - 
}

int main(int argc, char **argv){
    labyrinth_t *maze = read_labyrinth();
    print_labyrinth(maze);
}
