/*
** EPITECH PROJECT, 2024
** B-CPE-100-LYN-1-1-cpoolday04-luca.grange
** File description:
** my_strlen
*/

#include "my.h"

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        i++;
    }
    return i;
}
