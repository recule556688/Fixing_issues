/*
** EPITECH PROJECT, 2024
** B-CPE-100-LYN-1-1-cpoolday03-luca.grange
** File description:
** my_put_nbr
*/

#include "my.h"

int my_put_nbr(int nb)
{
    if (nb == -2147483648) {
        my_putchar('-');
        my_putchar('2');
        my_put_nbr(147483648);
        return 0;
    }
    if (nb < 0){
        my_putchar('-');
        nb = - nb;
    }
    if (nb >= 10){
        my_put_nbr(nb / 10);
    }
    my_putchar('0' + nb % 10);
    return 0;
}
