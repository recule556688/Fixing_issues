/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** filter_utils
*/

#include "dataframe.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static void *copy_int_value(void *value)
{
    int *new_val = malloc(sizeof(int));

    if (new_val)
        *(int *) new_val = *(int *) value;
    return new_val;
}

static void *copy_float_value(void *value)
{
    float *new_val = malloc(sizeof(float));

    if (new_val)
        *(float *) new_val = *(float *) value;
    return new_val;
}

static void *copy_string_value(void *value)
{
    return strdup((char *) value);
}

static void *copy_uint_value(void *value)
{
    unsigned int *new_val = malloc(sizeof(unsigned int));

    if (new_val)
        *(unsigned int *) new_val = *(unsigned int *) value;
    return new_val;
}

static void *copy_bool_value(void *value)
{
    bool *new_val = malloc(sizeof(bool));

    if (new_val)
        *(bool *) new_val = *(bool *) value;
    return new_val;
}

void *copy_column_value(void *value, char type)
{
    if (!value)
        return NULL;
    switch (type) {
        case 'i':
            return copy_int_value(value);
        case 'f':
            return copy_float_value(value);
        case 's':
            return copy_string_value(value);
        case 'u':
            return copy_uint_value(value);
        case 'b':
            return copy_bool_value(value);
        default:
            return NULL;
    }
}
