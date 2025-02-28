/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell1-luca.grange
** File description:
** String manipulation functions
*/

#ifndef MY_STRING_H_
    #define MY_STRING_H_

    #include <stddef.h>

typedef struct string_s {
    char *str;
    size_t len;
} string_t;

size_t my_strlen(const char *str);
char *my_strdup(const char *str);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, int n);
char *my_strchr(const char *s, int c);
int my_atoi(const char *s);

#endif /* !MY_STRING_H_ */
