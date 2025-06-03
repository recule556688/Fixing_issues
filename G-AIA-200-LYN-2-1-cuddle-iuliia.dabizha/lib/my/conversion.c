/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** Data type conversion functions
*/

#include "dataframe.h"
#include "struct.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *convert_int(const char *str)
{
    int *value = malloc(sizeof(int));

    if (value)
        *(int *) value = atoi(str);
    return value;
}

static void *convert_float(const char *str)
{
    float *value = malloc(sizeof(float));

    if (value)
        *(float *) value = atof(str);
    return value;
}

static void *convert_unsigned(const char *str)
{
    unsigned int *value = malloc(sizeof(unsigned int));

    if (value)
        *(unsigned int *) value = (unsigned int) strtoul(str, NULL, 10);
    return value;
}

static void *convert_bool(const char *str)
{
    bool *value = malloc(sizeof(bool));

    if (!value)
        return NULL;
    if (strcmp(str, "true") == 0 || strcmp(str, "1") == 0)
        *(bool *) value = true;
    else
        *(bool *) value = false;
    return value;
}

void *convert_value(const char *str, char type)
{
    if (!str)
        return NULL;
    switch (type) {
        case TYPE_INT:
            return convert_int(str);
        case TYPE_FLOAT:
            return convert_float(str);
        case TYPE_STRING:
            return strdup(str);
        case TYPE_UNSIGNED:
            return convert_unsigned(str);
        case TYPE_BOOL:
            return convert_bool(str);
        default:
            return NULL;
    }
}
