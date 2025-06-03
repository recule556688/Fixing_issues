/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** statistics_utils - Header for statistics utility functions
*/

#ifndef STATISTICS_UTILS_H_
    #define STATISTICS_UTILS_H_

    #include <stdbool.h>
    #include "dataframe.h"

bool is_numeric_type(char type);
double get_numeric_value(void *value, char type);
double calculate_mean(column_t *col, size_t *valid_count);
double calculate_min(column_t *col);
double calculate_max(column_t *col);
double calculate_std(column_t *col, double mean, size_t valid_count);

#endif /* !STATISTICS_UTILS_H_ */
