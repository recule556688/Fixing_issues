/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** handle_float
*/

#include "my.h"

int handle_unsigned_int(va_list list)
{
    unsigned int arg = va_arg(list, unsigned int);

    my_put_unsigned_nbr(arg);
    return num_char_in_uint(arg);
}
