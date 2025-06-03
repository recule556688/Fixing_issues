/*
** EPITECH PROJECT, 2024
** B-CPE-100-LYN-1-1-cpoolday08-iuliia.dabizha
** File description:
** my_strdup
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>

char *my_strdup(char const *src)
{
    char *str;

    str = malloc(sizeof(char) * (my_strlen(src) + 1));
    if (str == NULL) {
        return NULL;
    }
    my_strcpy(str, src);
    return str;
}
