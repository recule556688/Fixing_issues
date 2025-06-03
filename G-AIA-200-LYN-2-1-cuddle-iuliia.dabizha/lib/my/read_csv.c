/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** CSV reading functionality
*/

#include "dataframe.h"
#include "dataframe_utils.h"
#include "struct.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

data_type_t __attribute__((unused)) detect_type(const char *str)
{
    char *endptr = NULL;
    long val = 0;

    if (!str || !*str)
        return TYPE_STRING;
    val = strtol(str, &endptr, 10);
    if (*endptr == '\0')
        return (val < 0) ? TYPE_INT : TYPE_UNSIGNED;
    return TYPE_STRING;
}

dataframe_t *create_empty_dataframe(void)
{
    dataframe_t *df = malloc(sizeof(dataframe_t));

    if (!df)
        return NULL;
    df->nb_columns = 0;
    df->nb_rows = 0;
    df->columns = NULL;
    return df;
}

char determine_column_type(const char *header,
    const char **dtypes, size_t index)
{
    if (dtypes && dtypes[index]) {
        return dtypes[index][0];
    }
    if (strcmp(header, "age") == 0) {
        return TYPE_INT;
    }
    return TYPE_STRING;
}

int init_columns(dataframe_t *df, char **headers,
    size_t col_count, const char **dtypes)
{
    df->nb_columns = col_count;
    df->columns = malloc(sizeof(column_t *) * col_count);
    if (!df->columns)
        return -1;
    for (size_t i = 0; i < col_count; i++) {
        df->columns[i] = malloc(sizeof(column_t));
        if (!df->columns[i])
            return -1;
        df->columns[i]->name = headers[i];
        df->columns[i]->data = NULL;
        df->columns[i]->size = 0;
        df->columns[i]->type = determine_column_type(headers[i], dtypes, i);
    }
    return 0;
}

static int add_row_to_dataframe(dataframe_t *df, char **values,
    __attribute__((unused)) size_t value_count)
{
    df->nb_rows++;
    for (size_t i = 0; i < df->nb_columns; i++) {
        df->columns[i]->data =
            realloc(df->columns[i]->data, sizeof(void *) * df->nb_rows);
        if (!df->columns[i]->data)
            return -1;
        df->columns[i]->data[df->nb_rows - 1] =
            convert_value(values[i], df->columns[i]->type);
    }
    return 0;
}

static bool process_csv_header(csv_context_t *ctx, dataframe_t *df,
    const char **dtypes, char separator)
{
    char **headers = NULL;

    if (getline(&ctx->line, &ctx->len, ctx->file) == -1)
        return false;
    headers = split_line(ctx->line, &ctx->col_count, separator);
    if (!headers)
        return false;
    if (init_columns(df, headers, ctx->col_count, dtypes) != 0) {
        free(headers);
        return false;
    }
    free(headers);
    return true;
}

static dataframe_t *initialize_dataframe(const char *filename,
    const char **dtypes, char separator, csv_context_t *ctx)
{
    dataframe_t *df = NULL;

    if (!init_csv_context(ctx, filename))
        return NULL;
    df = create_empty_dataframe();
    if (!df || !process_csv_header(ctx, df, dtypes, separator)) {
        cleanup_csv_context(ctx, df);
        return NULL;
    }
    return df;
}

static int process_csv_row(dataframe_t *df, csv_context_t *ctx, char separator)
{
    char **values = NULL;
    size_t value_count = 0;

    if (strlen(ctx->line) <= 1)
        return 0;
    values = split_line(ctx->line, &value_count, separator);
    if (!values || add_row_to_dataframe(df, values, value_count) != 0) {
        free(values);
        return -1;
    }
    free(values);
    return 0;
}

dataframe_t *df_read_csv(const char *filename,
    const char **dtypes, char separator)
{
    csv_context_t ctx = {0};
    dataframe_t *df = NULL;

    df = initialize_dataframe(filename, dtypes, separator, &ctx);
    if (!df)
        return NULL;
    while (getline(&ctx.line, &ctx.len, ctx.file) != -1) {
        if (process_csv_row(df, &ctx, separator) != 0) {
            cleanup_csv_context(&ctx, df);
            return NULL;
        }
    }
    cleanup_csv_context(&ctx, NULL);
    return df;
}
