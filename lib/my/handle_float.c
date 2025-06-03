/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** handle_float
*/

#include "my.h"

int handle_float(va_list list)
{
    float arg = va_arg(list, double);
    format_spec_t spec = {0};

    return my_putfloat(arg, -1, spec);
}
