/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** handle_float
*/

#include "my.h"

int handle_char(va_list list)
{
    my_putchar((char) va_arg(list, int));
    return 1;
}
