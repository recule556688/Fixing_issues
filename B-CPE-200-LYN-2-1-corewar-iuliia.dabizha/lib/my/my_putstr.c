/*
** EPITECH PROJECT, 2024
** B-CPE-100-LYN-1-1-cpoolday04-luca.grange
** File description:
** my_put_str
*/
#include "my.h"

int my_putstr(char const *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len])
        my_putchar(str[len++]);
    return len;
}
