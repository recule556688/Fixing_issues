/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** statistics - Functions for statistical operations on dataframes
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dataframe.h"
#include "statistics_utils.h"

static void print_numeric_column_header(dataframe_t *df, size_t i,
    bool *has_numeric)
{
    if (is_numeric_type(df->columns[i]->type)) {
        printf("%-15s", df->columns[i]->name);
        *has_numeric = true;
    }
}

static void print_column_stat_headers(dataframe_t *dataframe,
    bool *has_numeric)
{
    size_t i;

    printf("%-10s", "");
    for (i = 0; i < dataframe->nb_columns; i++)
        print_numeric_column_header(dataframe, i, has_numeric);
}

static size_t count_valid_values(dataframe_t *df, size_t col_idx)
{
    size_t count = 0;
    size_t j;

    for (j = 0; j < df->nb_rows; j++) {
        if (df->columns[col_idx]->data[j])
            count++;
    }
    return count;
}

static void print_column_counts(dataframe_t *dataframe)
{
    size_t i;
    size_t count;

    printf("\n%-10s", "count");
    for (i = 0; i < dataframe->nb_columns; i++) {
        if (is_numeric_type(dataframe->columns[i]->type)) {
            count = count_valid_values(dataframe, i);
            printf("%-15zu", count);
        }
    }
}

static void print_column_means(dataframe_t *dataframe)
{
    size_t i;
    size_t valid_count;
    double mean;

    printf("\n%-10s", "mean");
    for (i = 0; i < dataframe->nb_columns; i++) {
        if (is_numeric_type(dataframe->columns[i]->type)) {
            mean = calculate_mean(dataframe->columns[i], &valid_count);
            printf("%-15.2f", mean);
        }
    }
}

static void print_column_stds(dataframe_t *dataframe)
{
    size_t i;
    size_t valid_count;
    double mean;
    double std_dev;

    printf("\n%-10s", "std");
    for (i = 0; i < dataframe->nb_columns; i++) {
        if (is_numeric_type(dataframe->columns[i]->type)) {
            mean = calculate_mean(dataframe->columns[i], &valid_count);
            std_dev = calculate_std(dataframe->columns[i], mean,
                valid_count);
            printf("%-15.2f", std_dev);
        }
    }
}

static void print_column_mins(dataframe_t *dataframe)
{
    size_t i;
    double min;

    printf("\n%-10s", "min");
    for (i = 0; i < dataframe->nb_columns; i++) {
        if (is_numeric_type(dataframe->columns[i]->type)) {
            min = calculate_min(dataframe->columns[i]);
            printf("%-15.2f", min);
        }
    }
}

static void print_column_maxes(dataframe_t *dataframe)
{
    size_t i;
    double max;

    printf("\n%-10s", "max");
    for (i = 0; i < dataframe->nb_columns; i++) {
        if (is_numeric_type(dataframe->columns[i]->type)) {
            max = calculate_max(dataframe->columns[i]);
            printf("%-15.2f", max);
        }
    }
}

void df_describe(dataframe_t *dataframe)
{
    bool has_numeric = false;

    if (!dataframe)
        return;
    printf("Statistics:\n");
    print_column_stat_headers(dataframe, &has_numeric);
    if (!has_numeric) {
        printf("No numeric columns to describe.\n");
        return;
    }
    print_column_counts(dataframe);
    print_column_means(dataframe);
    print_column_stds(dataframe);
    print_column_mins(dataframe);
    print_column_maxes(dataframe);
    printf("\n");
}
