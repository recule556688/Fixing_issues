/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** Write a string to stdout
*/

#include "my.h"

void my_putstr(const char *str)
{
    if (!str)
        return;
    while (*str) {
        my_putchar(*str);
        str++;
    }
}
