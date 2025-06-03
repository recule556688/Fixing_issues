/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** my_put_unsigned_nbr
*/

#include "my.h"

int my_put_unsigned_nbr(unsigned int nb)
{
    if (nb >= 10) {
        my_put_unsigned_nbr(nb / 10);
    }
    my_putchar('0' + (nb % 10));
    return 0;
}
