/*
** EPITECH PROJECT, 2024
** B-CPE-100-LYN-1-1-cpoolday03-luca.grange
** File description:
** my_putchar
*/

#include "my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
    return;
}
