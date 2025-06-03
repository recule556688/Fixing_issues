/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** handle_float
*/

#include "my.h"

int handle_string(va_list list)
{
    char *str = va_arg(list, char *);

    if (str == NULL)
        str = "(null)";
    my_putstr(str);
    return my_strlen(str);
}
