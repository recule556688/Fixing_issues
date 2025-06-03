/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** handle_float
*/

#include "my.h"

int handle_int(va_list list)
{
    int arg = va_arg(list, int);

    my_put_nbr(arg);
    return num_char_in_int(arg);
}
