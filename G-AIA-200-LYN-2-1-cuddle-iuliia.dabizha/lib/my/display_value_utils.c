/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** display_value_utils - Value-related utility functions for display operations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dataframe.h"
#include "display_value_utils.h"

void print_int_value(int *value)
{
    printf("%d", *value);
}

void print_float_value(float *value)
{
    printf("%.2f", *value);
}

void print_string_value(char *value)
{
    printf("%s", value);
}

void print_value(void *value, char type)
{
    if (!value) {
        printf("NA");
        return;
    }
    switch (type) {
        case 'i':
            print_int_value((int *)value);
            break;
        case 'f':
            print_float_value((float *)value);
            break;
        case 's':
            print_string_value((char *)value);
            break;
        default:
            printf("NA");
    }
}

const char *get_type_name(char type)
{
    switch (type) {
        case 'i':
            return "int";
        case 'u':
            return "unsigned int";
        case 'f':
            return "float";
        case 's':
            return "string";
        case 'b':
            return "bool";
        default:
            return "undefined";
    }
}
