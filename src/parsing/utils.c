/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-iuliia.dabizha
** File description:
** Utility functions
*/

#include "../include/maze.h"

char *detect_sep(char *str, char sep)
{
    char *c = str;

    if (!str)
        return NULL;
    while (*c) {
        if (*c == sep) {
            *c = '\0';
            return c + 1;
        }
        c++;
    }
    return NULL;
}

float my_sqrt(float nb)
{
    float t = nb / 2.0f;
    float eps = 0.00001f;
    float t2 = t * t;

    if (nb < 0)
        return -1;
    while ((t2 - nb) > eps || (nb - t2) > eps) {
        t = (t + nb / t) / 2.0f;
        t2 = t * t;
    }
    return t;
}
