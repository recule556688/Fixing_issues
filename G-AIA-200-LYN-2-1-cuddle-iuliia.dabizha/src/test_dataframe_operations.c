/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** test_dataframe_operations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/dataframe.h"


void test_filter(const char *filename)
{
    dataframe_t *df = df_read_csv(filename, NULL, ',');
    dataframe_t *filtered = NULL;

    if (!df) {
        printf("Failed to read CSV file\n");
        return;
    }
    filtered = df_filter(df, "age", filter_age_over_30);
    if (filtered) {
        printf("\nRows with age > 30:\n");
        df_write_csv(filtered, "filtered.csv");
        printf("Filtered data written to filtered.csv\n");
        df_free(filtered);
    } else {
        printf("No rows matched the filter or filter failed\n");
    }
    df_free(df);
}

void test_sort(const char *filename)
{
    dataframe_t *df = df_read_csv(filename, NULL, ',');
    dataframe_t *sorted = NULL;

    if (!df) {
        printf("Failed to read CSV file\n");
        return;
    }
    sorted = df_sort(df, "age", sort_age_desc);
    if (sorted) {
        printf("\nRows sorted by age (descending):\n");
        df_write_csv(sorted, "sorted.csv");
        printf("Sorted data written to sorted.csv\n");
        df_free(sorted);
    } else {
        printf("Sorting failed\n");
    }
    df_free(df);
}

void test_get_value(const char *filename)
{
    dataframe_t *df = df_read_csv(filename, NULL, ',');
    void *value;

    if (!df) {
        printf("Failed to read CSV file\n");
        return;
    }
    value = df_get_value(df, 0, "name");
    if (value) {
        printf("Value at row 0, column 'name': %s\n", (char *)value);
    }
    value = df_get_value(df, 1, "age");
    if (value) {
        printf("Value at row 1, column 'age': %d\n", *(int *)value);
    }
    df_free(df);
}

void test_get_unique_values(const char *filename)
{
    dataframe_t *df = df_read_csv(filename, NULL, ',');
    void **unique_values;

    if (!df) {
        printf("Failed to read CSV file\n");
        return;
    }
    *unique_values = df_get_unique_values(df, "city");
    if (unique_values) {
        printf("Unique values in 'city' column:\n");
        for (int i = 0; unique_values[i] != NULL; i++) {
            printf("- %s\n", (char *)unique_values[i]);
            free(unique_values[i]);
        }
        free(unique_values);
    }
    df_free(df);
}
