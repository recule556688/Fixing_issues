/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** statistics_advanced - Advanced statistical operations
*/

#include "dataframe.h"
#include "statistics_utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double calculate_square_diffs(column_t *col, double mean)
{
    double sum_squared_diff = 0.0;
    size_t i;
    double val;
    double diff;

    for (i = 0; i < col->size; i++) {
        if (col->data[i]) {
            val = get_numeric_value(col->data[i], col->type);
            diff = val - mean;
            sum_squared_diff += diff * diff;
        }
    }
    return sum_squared_diff;
}

double calculate_std(column_t *col, double mean, size_t valid_count)
{
    if (valid_count <= 1)
        return 0.0;
    return sqrt(calculate_square_diffs(col, mean) / (valid_count - 1));
}
