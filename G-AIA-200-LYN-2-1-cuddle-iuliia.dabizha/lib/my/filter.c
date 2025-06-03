/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** filter
*/

#include "dataframe.h"
#include "filter_utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void *df_get_value(dataframe_t *dataframe, int row, const char *column)
{
    int col_idx = find_column_index(dataframe, column);

    if (!dataframe || !column || row < 0 || row >= (int) dataframe->nb_rows)
        return NULL;
    if (col_idx < 0)
        return NULL;
    return dataframe->columns[col_idx]->data[row];
}

void **df_get_values(dataframe_t *dataframe, const char *column)
{
    int col_idx = find_column_index(dataframe, column);

    if (!dataframe || !column || col_idx < 0)
        return NULL;
    return dataframe->columns[col_idx]->data;
}

static bool are_values_equal(void *val1, void *val2, char type)
{
    if (val1 == NULL || val2 == NULL)
        return val1 == val2;
    switch (type) {
        case 'i':
            return *(int *) val1 == *(int *) val2;
        case 'f':
            return *(float *) val1 == *(float *) val2;
        case 's':
            return strcmp((char *) val1, (char *) val2) == 0;
        case 'u':
            return *(unsigned int *) val1 == *(unsigned int *) val2;
        case 'b':
            return *(bool *) val1 == *(bool *) val2;
        default:
            return false;
    }
}

static bool check_value_uniqueness(void *value, column_t *col, size_t start)
{
    for (size_t j = 0; j < start; j++) {
        if (are_values_equal(value, col->data[j], col->type))
            return false;
    }
    return true;
}

static size_t count_unique_values(column_t *col, dataframe_t *df)
{
    size_t unique_count = 0;

    for (size_t i = 0; i < df->nb_rows; i++) {
        if (check_value_uniqueness(col->data[i], col, i))
            unique_count++;
    }
    return unique_count;
}

static void **allocate_unique_values(size_t count)
{
    void **values = malloc(sizeof(void *) * (count + 1));

    if (!values)
        return NULL;
    values[count] = NULL;
    return values;
}

static bool init_unique_values_context(dataframe_t *dataframe,
    const char *column, unique_values_context_t *ctx)
{
    if (!dataframe || !column)
        return false;
    ctx->col_idx = find_column_index(dataframe, column);
    if (ctx->col_idx < 0)
        return false;
    ctx->col = dataframe->columns[ctx->col_idx];
    ctx->unique_count = count_unique_values(ctx->col, dataframe);
    ctx->values = allocate_unique_values(ctx->unique_count);
    return ctx->values != NULL;
}

static void fill_unique_values(column_t *col, dataframe_t *dataframe,
    void **values, size_t unique_count)
{
    size_t idx = 0;

    for (size_t i = 0; i < dataframe->nb_rows && idx < unique_count; i++) {
        if (check_value_uniqueness(col->data[i], col, i)) {
            values[idx] = copy_column_value(col->data[i], col->type);
            idx++;
        }
    }
}

void **df_get_unique_values(dataframe_t *dataframe, const char *column)
{
    unique_values_context_t ctx = {0};
    void **result;

    if (!init_unique_values_context(dataframe, column, &ctx))
        return NULL;
    fill_unique_values(ctx.col, dataframe, ctx.values, ctx.unique_count);
    result = ctx.values;
    return result;
}
