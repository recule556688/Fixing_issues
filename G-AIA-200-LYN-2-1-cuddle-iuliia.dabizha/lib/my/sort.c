/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** sort
*/

#include "dataframe.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

static void *copy_value_aux(void *value, char type)
{
    void *new_value = NULL;

    if (value && type == TYPE_BOOL){
        new_value = malloc(sizeof(bool));
        if (new_value)
            *(bool *) new_value = *(bool *) value;
    }
    if (value && type == TYPE_UNSIGNED){
        new_value = malloc(sizeof(unsigned int));
        if (new_value)
            *(unsigned int *) new_value = *(unsigned int *) value;
    }
    return new_value;
}

static void *copy_value(void *value, char type)
{
    void *new_value = NULL;

    new_value = copy_value_aux(value, type);
    if (value && type == TYPE_INT){
        new_value = malloc(sizeof(int));
        if (new_value)
            *(int *) new_value = *(int *) value;
    }
    if (value && type == TYPE_FLOAT){
        new_value = malloc(sizeof(float));
        if (new_value)
            *(float *) new_value = *(float *) value;
    }
    if (value && type == TYPE_STRING)
        new_value = strdup((char *) value);
    return new_value;
}

dataframe_t *init_dataframe(dataframe_t *src)
{
    dataframe_t *df = malloc(sizeof(dataframe_t));

    if (!df)
        return NULL;
    df->nb_columns = src->nb_columns;
    df->nb_rows = src->nb_rows;
    df->columns = malloc(sizeof(column_t *) * src->nb_columns);
    if (!df->columns) {
        free(df);
        return NULL;
    }
    return df;
}

int df_sort_aux_aux(dataframe_t *dataframe, size_t src_idx,
    dataframe_t *sorted_df, size_t i)
{
    for (size_t j = 0; j < dataframe->nb_columns; j++) {
        sorted_df->columns[j]->data[i] =
            copy_value(dataframe->columns[j]->data[src_idx],
                dataframe->columns[j]->type);
        if (!sorted_df->columns[j]->data[i]
            && dataframe->columns[j]->data[src_idx]) {
            return 84;
        }
    }
    return 0;
}

dataframe_t *df_sort_aux(dataframe_t *dataframe, size_t *indices)
{
    dataframe_t *sorted_df = create_empty_dataframe_two(dataframe);
    size_t src_idx;
    int t;

    if (!sorted_df) {
        return NULL;
    }
    for (size_t i = 0; i < dataframe->nb_rows; i++) {
        src_idx = indices[i];
        t = df_sort_aux_aux(dataframe, src_idx, sorted_df, i);
        if (t != 0) {
            df_free(sorted_df);
            return NULL;
        }
    }
    return sorted_df;
}

dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value2))
{
    int col_idx = find_column_index(dataframe, column);
    size_t *indices = NULL;
    sort_context_t context;
    dataframe_t *sorted_df;

    if (dataframe && column && sort_func && col_idx >= 0)
        indices = malloc(sizeof(size_t) * dataframe->nb_rows);
    if (!indices)
        return NULL;
    for (size_t i = 0; i < dataframe->nb_rows; i++)
        indices[i] = i;
    context.df = dataframe;
    context.col_idx = col_idx;
    context.sort_func = sort_func;
    sort_indices(indices, dataframe->nb_rows, &context);
    sorted_df = df_sort_aux(dataframe, indices);
    free(indices);
    return sorted_df;
}
