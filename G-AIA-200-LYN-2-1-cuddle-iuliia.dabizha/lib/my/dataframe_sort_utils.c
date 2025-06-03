/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** dataframe_sort_utils
*/

#include "dataframe.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

int find_column_index(dataframe_t *dataframe, const char *column_name)
{
    if (!dataframe || !column_name)
        return -1;
    for (size_t i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->columns[i]->name, column_name) == 0)
            return (int) i;
    }
    return -1;
}

int compare_rows_wrapper(const void *a, const void *b)
{
    sort_context_t *g_sort_context = NULL;
    size_t idx1 = *(size_t *) a;
    size_t idx2 = *(size_t *) b;
    void *val1 =
        g_sort_context->df->columns[g_sort_context->col_idx]->data[idx1];
    void *val2 =
        g_sort_context->df->columns[g_sort_context->col_idx]->data[idx2];

    if (g_sort_context->sort_func(val1, val2))
        return 1;
    if (g_sort_context->sort_func(val2, val1))
        return -1;
    return 0;
}

column_t *create_empty_column(dataframe_t *src, column_t *src_col)
{
    column_t *newCol = malloc(sizeof(column_t));

    if (!newCol)
        return NULL;
    newCol->name = strdup(src_col->name);
    newCol->type = src_col->type;
    newCol->size = src->nb_rows;
    if (!newCol->name){
        free_column(newCol, src->nb_rows);
        return NULL;
    }
    newCol->data = calloc(src->nb_rows, sizeof(void *));
    if (!newCol->data) {
        free_column(newCol, src->nb_rows);
        return NULL;
    }
    return newCol;
}

dataframe_t *create_empty_dataframe_two(dataframe_t *src)
{
    dataframe_t *df = init_dataframe(src);

    if (!df)
        return NULL;
    for (size_t i = 0; i < src->nb_columns; i++) {
        df->columns[i] = create_empty_column(src, src->columns[i]);
        if (!df->columns[i]) {
            df_free(df);
            return NULL;
        }
    }
    return df;
}

void sort_indices(size_t *indices, size_t count,
    sort_context_t *context)
{
    sort_context_t *g_sort_context = NULL;

    g_sort_context = context;
    qsort(indices, count, sizeof(size_t), compare_rows_wrapper);
    g_sort_context = NULL;
}
