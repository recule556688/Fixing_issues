/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/dataframe.h"

bool filter_age_over_30(void *value)
{
    if (!value)
        return false;
    return *(int *)value > 50;
}

bool sort_age_desc(void *value1, void *value2)
{
    if (!value1 || !value2)
        return false;
    return *(int *)value1 > *(int *)value2;
}

static void test_custom_separator(const char *filename, char separator)
{
    dataframe_t *df = df_read_csv(filename, NULL, separator);

    if (!df) {
        printf("Failed to read file with custom separator\n");
        return;
    }
    printf("\nDataframe with custom separator '%c':\n", separator);
    df_info(df);
    df_write_csv(df, "custom_separator.csv");
    printf("Data written to custom_separator.csv\n");
    df_free(df);
}

static void test_custom_dtypes(const char *filename)
{
    const char *dtypes[] = {"i", "f", "s", "u", "b", NULL};
    dataframe_t *df = df_read_csv(filename, dtypes, ',');

    if (!df) {
        printf("Failed to read CSV file with custom dtypes\n");
        return;
    }
    printf("\nDataframe with custom dtypes:\n");
    df_info(df);
    df_free(df);
}

void print_help(char *av0)
{
    printf("Usage: %s <command> <csv_file> [separator]\n", av0);
    printf("Commands:\n");
    printf("  head     - Show first 3 rows\n");
    printf("  tail     - Show last 3 rows\n");
    printf("  info     - Show dataframe info\n");
    printf("  describe - Show numerical columns statistics\n");
    printf("  shape    - Show dataframe dimensions\n");
    printf("  filter   - Filter rows with age > 30\n");
    printf("  sort     - Sort rows by age (descending)\n");
    printf("  value    - Get a specific value\n");
    printf("  unique   - Get unique values from a column\n");
    printf("  custom   - Use a custom separator\n");
    printf("  custom-dtypes - Test custom data types\n");
}

static int main_aux_one(char **av)
{
    if (strcmp(av[1], "head") == 0) {
        test_head(av[2]);
        return 0;
    }
    if (strcmp(av[1], "tail") == 0) {
        test_tail(av[2]);
        return 0;
    }
    if (strcmp(av[1], "info") == 0) {
        test_info(av[2]);
        return 0;
    }
    if (strcmp(av[1], "describe") == 0) {
        test_describe(av[2]);
        return 0;
    }
    return -1;
}

static int main_aux_two(char **av)
{
    if (strcmp(av[1], "shape") == 0) {
        test_shape(av[2]);
        return 0;
    }
    if (strcmp(av[1], "filter") == 0) {
        test_filter(av[2]);
        return 0;
    }
    if (strcmp(av[1], "sort") == 0) {
        test_sort(av[2]);
        return 0;
    }
    if (strcmp(av[1], "value") == 0) {
        test_get_value(av[2]);
        return 0;
    }
    return -1;
}

static int main_aux_three(int ac, char **av)
{
    if (strcmp(av[1], "unique") == 0) {
        test_get_unique_values(av[2]);
        return 0;
    }
    if (strcmp(av[1], "custom") == 0) {
        if (ac < 4) {
            printf("Error: custom command requires a separator character\n");
            printf("Usage: %s custom <file> <separator>\n", av[0]);
            return 84;
        }
        test_custom_separator(av[2], av[3][0]);
        return 0;
    }
    return -1;
}

static int main_aux_four(char **av)
{
    if (strcmp(av[1], "custom-dtypes") == 0) {
        test_custom_dtypes(av[2]);
        return 0;
    } else {
        printf("Unknown command: %s\n", av[1]);
        return 84;
    }
}

int main(int ac, char **av)
{
    int t = 84;

    if (ac < 3) {
        print_help(av[0]);
        return 84;
    }
    t = main_aux_one(av);
    if (t < 0) {
        t = main_aux_two(av);
    }
    if (t < 0) {
        main_aux_three(ac, av);
    }
    if (t < 0) {
        t = main_aux_four(av);
    }
    return t;
}
