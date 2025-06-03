/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** filter_init
*/

#include "dataframe.h"
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "filter_utils.h"

static int init_column(dataframe_t *filtered, dataframe_t *src, size_t i)
{
    filtered->columns[i] = malloc(sizeof(column_t));
    if (!filtered->columns[i])
        return -1;
    filtered->columns[i]->name = strdup(src->columns[i]->name);
    if (!filtered->columns[i]->name)
        return -1;
    filtered->columns[i]->type = src->columns[i]->type;
    filtered->columns[i]->data = NULL;
    filtered->columns[i]->size = 0;
    return 0;
}

dataframe_t *init_filtered_dataframe(dataframe_t *src)
{
    dataframe_t *filtered = malloc(sizeof(dataframe_t));

    if (!filtered)
        return NULL;
    filtered->nb_columns = src->nb_columns;
    filtered->nb_rows = 0;
    filtered->columns = malloc(sizeof(column_t *) * src->nb_columns);
    if (!filtered->columns) {
        free(filtered);
        return NULL;
    }
    for (size_t i = 0; i < src->nb_columns; i++) {
        if (init_column(filtered, src, i) != 0) {
            df_free(filtered);
            return NULL;
        }
    }
    return filtered;
}

static int copy_matching_row(dataframe_t *filtered, dataframe_t *src,
    size_t row_idx)
{
    void *value;

    for (size_t j = 0; j < src->nb_columns; j++) {
        value = copy_column_value(src->columns[j]->data[row_idx],
                src->columns[j]->type);
        if (!value && src->columns[j]->data[row_idx])
            return -1;
        filtered->columns[j]->data =
            realloc(filtered->columns[j]->data,
                sizeof(void *) * (filtered->nb_rows + 1));
        filtered->columns[j]->data[filtered->nb_rows] = value;
        filtered->columns[j]->size = filtered->nb_rows + 1;
    }
    filtered->nb_rows++;
    return 0;
}

dataframe_t *df_filter(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *value))
{
    int col_idx;
    dataframe_t *filtered;

    if (!dataframe || !column || !filter_func)
        return NULL;
    col_idx = find_column_index(dataframe, column);
    if (col_idx < 0)
        return NULL;
    filtered = init_filtered_dataframe(dataframe);
    if (!filtered)
        return NULL;
    for (size_t i = 0; i < dataframe->nb_rows; i++) {
        if (!filter_func(dataframe->columns[col_idx]->data[i]))
            continue;
        if (copy_matching_row(filtered, dataframe, i) != 0) {
            df_free(filtered);
            return NULL;
        }
    }
    return filtered;
}
