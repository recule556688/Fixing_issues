/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** handle_unsigned_int_octal
*/

#include "my.h"

int handle_unsigned_int_octal(va_list list)
{
    unsigned int arg = va_arg(list, unsigned int);
    int len = 0;

    if ((int)arg < 0) {
        len = my_put_unsigned_nbr_base(arg, OCTAL);
    } else {
        len = my_put_unsigned_nbr_base(arg, OCTAL);
    }
    return len;
}
