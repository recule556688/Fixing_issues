/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** print_specials
*/

#include "my.h"

int print_specials(char specifier)
{
    switch (specifier) {
    case '%':
        my_putchar('%');
        return 1;
    default:
        return 0;
    }
}
