/*
** EPITECH PROJECT, 2025
** my_putnbr.c
** File description:
** Print a number to stdout
*/

#include <unistd.h>
#include "my.h"

void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10) {
        my_putnbr(nb / 10);
    }
    my_putchar((nb % 10) + '0');
}
