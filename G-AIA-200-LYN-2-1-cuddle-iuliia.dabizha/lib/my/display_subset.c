/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** display_subset - Functions for displaying dataframe subsets
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dataframe.h"
#include "display_utils.h"
#include "display_copy_utils.h"
#include "display_subset.h"

static bool allocate_column_resources(column_t *new_col, column_t *col,
    size_t count)
{
    new_col->name = strdup(col->name);
    new_col->data = malloc(sizeof(void *) * count);
    if (!new_col->name || !new_col->data) {
        free(new_col->name);
        free(new_col->data);
        free(new_col);
        return false;
    }
    return true;
}

static void free_partial_column(column_t *col, size_t count)
{
    for (size_t j = 0; j < count; j++)
        free(col->data[j]);
    free(col->name);
    free(col->data);
    free(col);
}

static bool copy_column_data(column_t *new_col, column_t *col,
    size_t start, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        new_col->data[i] = copy_value(col->data[start + i], col->type);
        if (col->data[start + i] && !new_col->data[i]) {
            free_partial_column(new_col, i);
            return false;
        }
    }
    return true;
}

static column_t *copy_column(column_t *col, size_t start, size_t count)
{
    column_t *new_col = malloc(sizeof(column_t));

    if (!new_col)
        return NULL;
    new_col->type = col->type;
    new_col->size = count;
    if (!allocate_column_resources(new_col, col, count))
        return NULL;
    if (!copy_column_data(new_col, col, start, count))
        return NULL;
    return new_col;
}

static void free_partial_df_column(dataframe_t *df, size_t col_idx,
    size_t row_count)
{
    for (size_t k = 0; k < row_count; k++)
        free(df->columns[col_idx]->data[k]);
    free(df->columns[col_idx]->name);
    free(df->columns[col_idx]->data);
    free(df->columns[col_idx]);
}

static void free_partial_dataframe(dataframe_t *df, size_t col_count,
    size_t row_count)
{
    for (size_t j = 0; j < col_count; j++)
        free_partial_df_column(df, j, row_count);
    free(df->columns);
    free(df);
}

static bool create_df_columns(dataframe_t *new_df, dataframe_t *df,
    size_t start, size_t rows)
{
    for (size_t i = 0; i < df->nb_columns; i++) {
        new_df->columns[i] = copy_column(df->columns[i], start, rows);
        if (!new_df->columns[i]) {
            free_partial_dataframe(new_df, i, rows);
            return false;
        }
    }
    return true;
}

static dataframe_t *create_subset_dataframe(dataframe_t *df, size_t start,
    size_t rows)
{
    dataframe_t *new_df = malloc(sizeof(dataframe_t));

    if (!new_df)
        return NULL;
    new_df->nb_rows = rows;
    new_df->nb_columns = df->nb_columns;
    new_df->columns = malloc(sizeof(column_t *) * df->nb_columns);
    if (!new_df->columns) {
        free(new_df);
        return NULL;
    }
    if (!create_df_columns(new_df, df, start, rows))
        return NULL;
    return new_df;
}

dataframe_t *df_head(dataframe_t *dataframe, int nb_rows)
{
    size_t rows;

    if (!dataframe || nb_rows <= 0)
        return NULL;
    rows = (size_t)nb_rows;
    if (rows > dataframe->nb_rows)
        rows = dataframe->nb_rows;
    return create_subset_dataframe(dataframe, 0, rows);
}

dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows)
{
    size_t rows;
    size_t start;

    if (!dataframe || nb_rows <= 0)
        return NULL;
    rows = (size_t)nb_rows;
    if (rows > dataframe->nb_rows)
        rows = dataframe->nb_rows;
    start = dataframe->nb_rows - rows;
    return create_subset_dataframe(dataframe, start, rows);
}
