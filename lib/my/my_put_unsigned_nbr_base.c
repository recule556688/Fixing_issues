/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** my_put_unsigned_nbr_base
*/

#include "my.h"

int my_put_unsigned_nbr_base(unsigned int nbr, char const *base)
{
    unsigned int len_base = my_strlen(base);
    unsigned int result = 0;

    if (nbr >= len_base) {
        result += my_put_unsigned_nbr_base(nbr / len_base, base);
        my_putchar(base[(int)(nbr % len_base)]);
        result++;
    } else {
        my_putchar(base[(int)nbr]);
        result++;
    }
    return result;
}
