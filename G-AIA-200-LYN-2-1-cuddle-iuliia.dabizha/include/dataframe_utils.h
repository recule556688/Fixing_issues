/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** Dataframe utilities header
*/

#ifndef DATAFRAME_UTILS_H_
    #define DATAFRAME_UTILS_H_

    #include <stdbool.h>
    #include <stddef.h>

/* Conversion functions */
void *convert_value(const char *str, char type);

/* Token handling functions */
size_t count_fields(const char *line, char separator);
bool allocate_tokens(char ***tokens, size_t num_fields);
void free_tokens_and_copy(char **tokens, size_t size, char *line_copy);
bool process_token(char **tokens, size_t *size, char *token);
char **split_line(char *line, size_t *count, char separator);

#endif /* DATAFRAME_UTILS_H_ */
