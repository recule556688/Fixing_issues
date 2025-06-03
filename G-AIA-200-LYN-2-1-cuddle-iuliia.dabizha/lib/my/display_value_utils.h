/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** display_value_utils - Header for value display utility functions
*/

#ifndef DISPLAY_VALUE_UTILS_H_
    #define DISPLAY_VALUE_UTILS_H_

    #include "dataframe.h"

void print_int_value(int *value);
void print_float_value(float *value);
void print_string_value(char *value);
void print_value(void *value, char type);
const char *get_type_name(char type);

#endif /* !DISPLAY_VALUE_UTILS_H_ */
