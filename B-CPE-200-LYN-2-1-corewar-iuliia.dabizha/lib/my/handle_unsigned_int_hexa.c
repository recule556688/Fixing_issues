/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** handle_unsigned_int_hexa
*/

#include "my.h"

int handle_unsigned_int_hexa(va_list list, char *base)
{
    unsigned int arg = va_arg(list, unsigned int);
    int len = 0;
    char buffer[32];
    int i = 0;

    if ((int)arg < 0) {
        len = my_put_unsigned_nbr_base(arg, base);
    } else {
        len = my_put_unsigned_nbr_base(arg, base);
    }
    return len;
}
