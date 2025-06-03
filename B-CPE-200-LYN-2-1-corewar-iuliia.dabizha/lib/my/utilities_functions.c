/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-miniprintf-luca.grange
** File description:
** miniprintf
*/

#include "my.h"

int num_char_in_int(int n)
{
    int count = 0;

    if (n == 0) {
        return 1;
    }
    if (n < 0) {
        count++;
        n = -n;
    }
    while (n > 0) {
        n /= 10;
        count++;
    }
    return count;
}

int num_char_in_uint(unsigned int n)
{
    int count = 0;

    if (n == 0) {
        return 1;
    }
    while (n > 0) {
        n /= 10;
        count++;
    }
    return count;
}

long long my_dec_pow(int exp)
{
    long long val = 1;

    while (exp > 0) {
        val *= 10;
        --exp;
    }
    return val;
}
