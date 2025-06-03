/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** display - Functions for displaying dataframe content
*/

#include "dataframe.h"
#include "display_utils.h"
#include "display_value_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void df_info(dataframe_t *dataframe)
{
    if (!dataframe)
        return;
    printf("%zu columns:\n", dataframe->nb_columns);
    for (size_t i = 0; i < dataframe->nb_columns; i++) {
        printf("- %s: %s\n", dataframe->columns[i]->name,
            get_type_name(dataframe->columns[i]->type));
    }
}

dataframe_shape_t df_shape(dataframe_t *dataframe)
{
    dataframe_shape_t shape = {0, 0};

    if (!dataframe || !dataframe->columns || dataframe->nb_columns == 0)
        return shape;
    shape.nb_rows = dataframe->nb_rows;
    shape.nb_columns = dataframe->nb_columns;
    return shape;
}
