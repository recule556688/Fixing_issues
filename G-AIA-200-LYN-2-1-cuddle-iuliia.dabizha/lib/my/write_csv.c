/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** write_csv
*/

#include <stdio.h>
#include <stdlib.h>
#include "dataframe.h"

static void write_header(FILE *file, dataframe_t *df)
{
    for (size_t i = 0; i < df->nb_columns; i++) {
        fprintf(file, "%s", df->columns[i]->name);
        if (i < df->nb_columns - 1)
            fprintf(file, ",");
    }
    fprintf(file, "\n");
}

static void write_value(FILE *file, void *value, char type)
{
    if (!value) {
        fprintf(file, "NA");
        return;
    }
    switch (type) {
        case 'i':
            fprintf(file, "%d", *(int *)value);
            break;
        case 'f':
            fprintf(file, "%f", *(float *)value);
            break;
        case 's':
            fprintf(file, "%s", (char *)value);
            break;
        default:
            fprintf(file, "NA");
    }
}

static void write_row(FILE *file, dataframe_t *dataframe, size_t row_index)
{
    for (size_t j = 0; j < dataframe->nb_columns; j++) {
        write_value(file, dataframe->columns[j]->data[row_index],
            dataframe->columns[j]->type);
        if (j < dataframe->nb_columns - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");
}

int df_write_csv(dataframe_t *dataframe, const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (!file || !dataframe) {
        return -1;
    }
    write_header(file, dataframe);
    for (size_t i = 0; i < dataframe->nb_rows; i++) {
        write_row(file, dataframe, i);
    }
    fclose(file);
    return 0;
}
