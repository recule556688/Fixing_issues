/*
** EPITECH PROJECT, 2025
** my_strcmp
** File description:
** Compare two strings
*/

int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
} 