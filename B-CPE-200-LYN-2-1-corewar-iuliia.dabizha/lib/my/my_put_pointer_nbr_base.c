/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** my_put_pointer_nbr_base
*/

#include "my.h"

int my_put_pointer_nbr_base(unsigned long long nbr, char const *base)
{
    unsigned int len_base = my_strlen(base);
    int result = 0;

    if (nbr >= len_base) {
        result += my_put_pointer_nbr_base(nbr / len_base, base);
        my_putchar(base[nbr % len_base]);
        result++;
    } else {
        my_putchar(base[nbr]);
        result++;
    }
    return result;
}
