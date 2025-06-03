/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** free
*/

#include "dataframe.h"
#include <stdlib.h>

static void free_column_data(column_t *column, size_t nb_rows)
{
    if (!column->data)
        return;
    for (size_t j = 0; j < nb_rows; j++)
        free(column->data[j]);
    free(column->data);
}

void free_column(column_t *column, size_t nb_rows)
{
    if (!column)
        return;
    if (column->name)
        free(column->name);
    free_column_data(column, nb_rows);
    free(column);
}

void df_free(dataframe_t *dataframe)
{
    if (!dataframe)
        return;
    if (dataframe->columns) {
        for (size_t i = 0; i < dataframe->nb_columns; i++)
            free_column(dataframe->columns[i], dataframe->nb_rows);
        free(dataframe->columns);
    }
    free(dataframe);
}
