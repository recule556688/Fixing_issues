/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** dataframe
*/

#include <stdbool.h>
#include "struct.h"

#ifndef DATAFRAME_H_
    #define DATAFRAME_H_

// Core functions
dataframe_t *df_read_csv(const char *filename, const char **dtypes,
    char separator);
int df_write_csv(dataframe_t *dataframe, const char *filename);
void *df_get_value(dataframe_t *dataframe, int row, const char *column);
void **df_get_values(dataframe_t *dataframe, const char *column);
void **df_get_unique_values(dataframe_t *dataframe, const char *column);
void df_free(dataframe_t *dataframe);

// Display functions
dataframe_t *df_head(dataframe_t *dataframe, int nb_rows);
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows);
void df_info(dataframe_t *dataframe);
void df_describe(dataframe_t *dataframe);
dataframe_shape_t df_shape(dataframe_t *dataframe);
dataframe_t *df_filter(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *value));
dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value2));
void cleanup_csv_context(csv_context_t *ctx, dataframe_t *df);
bool init_csv_context(csv_context_t *ctx, const char *filename);
dataframe_t *create_empty_dataframe_two(dataframe_t *src);
column_t *create_empty_column(dataframe_t *src, column_t *src_col);
int compare_rows_wrapper(const void *a, const void *b);
int find_column_index(dataframe_t *dataframe, const char *column_name);
dataframe_t *init_dataframe(dataframe_t *src);
void free_column(column_t *column, size_t nb_rows);
bool filter_age_over_30(void *value);
bool sort_age_desc(void *value1, void *value2);
void test_filter(const char *filename);
void test_sort(const char *filename);
void test_get_value(const char *filename);
void test_get_unique_values(const char *filename);
void test_head(const char *filename);
void test_tail(const char *filename);
void test_info(const char *filename);
void test_describe(const char *filename);
void test_shape(const char *filename);

#endif /* !DATAFRAME_H_ */
