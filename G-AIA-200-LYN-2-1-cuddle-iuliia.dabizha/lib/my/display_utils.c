/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** display_utils - Helper functions for display operations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dataframe.h"
#include "display_utils.h"
#include "display_value_utils.h"

void print_row(dataframe_t *df, size_t row)
{
    for (size_t i = 0; i < df->nb_columns; i++) {
        print_value(df->columns[i]->data[row], df->columns[i]->type);
        if (i < df->nb_columns - 1)
            printf(",");
    }
    printf("\n");
}
