/*
** EPITECH PROJECT, 2025
** my_strdup
** File description:
** Duplicate a string
*/

#include <stdlib.h>

char *my_strdup(const char *src)
{
    int len = 0;
    char *dest;

    if (!src)
        return NULL;
    while (src[len])
        len++;
    dest = malloc(sizeof(char) * (len + 1));
    if (!dest)
        return NULL;
    len = 0;
    while (src[len]) {
        dest[len] = src[len];
        len++;
    }
    dest[len] = '\0';
    return dest;
} 