/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** handle_pointer
*/

#include "my.h"

int handle_pointer(unsigned long long arg)
{
    int result = 0;
    unsigned long long value = (unsigned long long)arg;

    my_putstr("0x");
    result += 2;
    result += my_put_pointer_nbr_base(value, HEXA_LOW);
    return result;
}
