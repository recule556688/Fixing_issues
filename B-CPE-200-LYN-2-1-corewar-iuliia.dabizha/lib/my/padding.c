/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha (Copy)
** File description:
** padding
*/

#include "my.h"

int print_padding(int width, int content_len, int zero_pad)
{
    int pad_len = width - content_len;
    int count = 0;

    while (pad_len > 0) {
        my_putchar(zero_pad ? '0' : ' ');
        count++;
        pad_len--;
    }
    return count;
}
