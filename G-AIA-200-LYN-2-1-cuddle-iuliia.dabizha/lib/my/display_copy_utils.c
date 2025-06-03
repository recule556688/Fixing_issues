/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** display_copy_utils - Copy-related utility functions for display operations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dataframe.h"
#include "display_copy_utils.h"

void *copy_int_value(int *value)
{
    int *new_value = malloc(sizeof(int));

    if (new_value)
        *new_value = *value;
    return new_value;
}

void *copy_float_value(float *value)
{
    float *new_value = malloc(sizeof(float));

    if (new_value)
        *new_value = *value;
    return new_value;
}

void *copy_string_value(char *value)
{
    return strdup(value);
}

void *copy_value(void *value, char type)
{
    if (!value)
        return NULL;
    switch (type) {
        case 'i':
            return copy_int_value((int *)value);
        case 'f':
            return copy_float_value((float *)value);
        case 's':
            return copy_string_value((char *)value);
        default:
            return NULL;
    }
}
