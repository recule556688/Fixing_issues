/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    #include <stddef.h>
    #include <stdio.h>

typedef enum data_type {
    TYPE_INT = 'i',
    TYPE_FLOAT = 'f',
    TYPE_STRING = 's',
    TYPE_UNSIGNED = 'u',
    TYPE_BOOL = 'b'
} data_type_t;

typedef struct column {
    char *name;
    void **data;
    size_t size;
    data_type_t type;
} column_t;

typedef struct dataframe {
    column_t **columns;
    size_t nb_columns;
    size_t nb_rows;
} dataframe_t;

typedef struct dataframe_shape_s {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

typedef struct {
    int col_idx;
    column_t *col;
    size_t unique_count;
    void **values;
} unique_values_context_t;

typedef struct csv_context_s {
    FILE *file;
    char *line;
    size_t len;
    size_t col_count;
} csv_context_t;

#endif /* !STRUCT_H_ */
