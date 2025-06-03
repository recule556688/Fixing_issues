/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** test_dataframe_io
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/dataframe.h"

void test_head(const char *filename)
{
    dataframe_t *df = df_read_csv(filename, NULL, ',');
    dataframe_t *head = NULL;

    if (!df) {
        printf("Failed to read CSV file\n");
        return;
    }
    head = df_head(df, 3);
    if (head) {
        printf("\nFirst 3 rows:\n");
        df_write_csv(head, "head.csv");
        printf("Head data written to head.csv\n");
        df_free(head);
    }
    df_free(df);
}

void test_tail(const char *filename)
{
    dataframe_t *df = df_read_csv(filename, NULL, ',');
    dataframe_t *tail = NULL;

    if (!df) {
        printf("Failed to read CSV file\n");
        return;
    }
    tail = df_tail(df, 3);
    if (tail) {
        printf("\nLast 3 rows:\n");
        df_write_csv(tail, "tail.csv");
        printf("Tail data written to tail.csv\n");
        df_free(tail);
    }
    df_free(df);
}

void test_info(const char *filename)
{
    dataframe_t *df = df_read_csv(filename, NULL, ',');

    if (!df) {
        printf("Failed to read CSV file\n");
        return;
    }
    printf("\nDataframe info:\n");
    df_info(df);
    df_free(df);
}

void test_describe(const char *filename)
{
    dataframe_t *df = df_read_csv(filename, NULL, ',');

    if (!df) {
        printf("Failed to read CSV file\n");
        return;
    }
    df_describe(df);
    df_free(df);
}

void test_shape(const char *filename)
{
    dataframe_t *df = df_read_csv(filename, NULL, ',');
    dataframe_shape_t shape;

    if (!df) {
        printf("Failed to read CSV file\n");
        return;
    }
    shape = df_shape(df);
    printf("Shape: %d rows, %d columns\n", shape.nb_rows, shape.nb_columns);
    df_free(df);
}
