/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** display_copy_utils - Header for copy display utility functions
*/

#ifndef DISPLAY_COPY_UTILS_H_
    #define DISPLAY_COPY_UTILS_H_

    #include "dataframe.h"

void *copy_int_value(int *value);
void *copy_float_value(float *value);
void *copy_string_value(char *value);
void *copy_value(void *value, char type);

#endif /* !DISPLAY_COPY_UTILS_H_ */
