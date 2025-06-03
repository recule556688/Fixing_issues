/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** statistics_utils
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "dataframe.h"

bool is_numeric_type(char type)
{
    return type == 'i' || type == 'u' || type == 'f';
}

double get_numeric_value(void *value, char type)
{
    if (!value)
        return 0.0;
    switch (type) {
        case 'i':
            return (double)(*(int *)value);
        case 'u':
            return (double)(*(unsigned int *)value);
        case 'f':
            return (double)(*(float *)value);
        default:
            return 0.0;
    }
}

static void accumulate_sum(column_t *col, double *sum, size_t *count)
{
    size_t i;
    double val;

    for (i = 0; i < col->size; i++) {
        if (col->data[i]) {
            val = get_numeric_value(col->data[i], col->type);
            *sum += val;
            (*count)++;
        }
    }
}

double calculate_mean(column_t *col, size_t *valid_count)
{
    double sum = 0.0;

    *valid_count = 0;
    accumulate_sum(col, &sum, valid_count);
    return *valid_count > 0 ? sum / *valid_count : 0.0;
}

double calculate_min(column_t *col)
{
    double min = INFINITY;
    bool has_value = false;
    size_t i;
    double val;

    for (i = 0; i < col->size; i++) {
        if (!col->data[i])
            continue;
        val = get_numeric_value(col->data[i], col->type);
        if (!has_value || val < min) {
            min = val;
            has_value = true;
        }
    }
    return has_value ? min : 0.0;
}

double calculate_max(column_t *col)
{
    double max = -INFINITY;
    bool has_value = false;
    size_t i;
    double val;

    for (i = 0; i < col->size; i++) {
        if (!col->data[i])
            continue;
        val = get_numeric_value(col->data[i], col->type);
        if (!has_value || val > max) {
            max = val;
            has_value = true;
        }
    }
    return has_value ? max : 0.0;
}

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
