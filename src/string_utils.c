/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell1-luca.grange
** File description:
** Basic string utility functions
*/

#include "../includes/my_string.h"
#include <stdlib.h>
#include <unistd.h>

size_t my_strlen(const char *s)
{
    size_t i = 0;

    while (s[i])
        i++;
    return i;
}

char *my_strdup(const char *s)
{
    size_t len = my_strlen(s);
    char *dup = malloc(len + 1);

    if (!dup) {
        write(2, "Error: malloc failed\n", 23);
        exit(84);
    }
    for (size_t i = 0; i <= len; i++)
        dup[i] = s[i];
    return dup;
}

int my_atoi(const char *s)
{
    int sign = 1;
    int result = 0;
    int i = 0;

    if (s[0] == '-') {
        sign = -1;
        i++;
    }
    while (s[i]) {
        result = result * 10 + (s[i] - '0');
        i++;
    }
    return result * sign;
}
