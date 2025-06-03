/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** Token and string handling utilities
*/

#include "dataframe.h"
#include "struct.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_fields(const char *line, char separator)
{
    size_t num_fields = 1;

    if (!line){
        return 0;
    }
    for (const char *p = line; *p; p++) {
        if (*p == separator)
            num_fields++;
    }
    return num_fields;
}

void free_tokens_and_copy(char **tokens, size_t size, char *line_copy)
{
    for (size_t i = 0; i < size; i++)
        free(tokens[i]);
    free(tokens);
    free(line_copy);
}

bool process_token(char **tokens, size_t *size, char *token)
{
    tokens[*size] = strdup(token);
    if (!tokens[*size])
        return false;
    (*size)++;
    return true;
}

char **tokenize_line(char *line_copy, size_t *size, size_t num_fields,
    const char *delim_str)
{
    char *token;
    char **tokens = calloc(num_fields, sizeof(char *));

    if (!tokens)
        return NULL;
    token = strtok(line_copy, delim_str);
    while (token != NULL && *size < num_fields) {
        if (!process_token(tokens, size, token)) {
            free_tokens_and_copy(tokens, *size, line_copy);
            return NULL;
        }
        token = strtok(NULL, delim_str);
    }
    return tokens;
}

char **split_line(char *line, size_t *count, char separator)
{
    char **tokens = NULL;
    char delim_str[4] = {separator, '\n', '\0'};
    size_t num_fields = count_fields(line, separator);
    char *line_copy = line ? strdup(line) : NULL;

    if (!line_copy){
        *count = 0;
        return NULL;
    }
    tokens = tokenize_line(line_copy, count, num_fields, delim_str);
    if (!tokens) {
        *count = 0;
        return NULL;
    }
    free(line_copy);
    return tokens;
}
