/*
** EPITECH PROJECT, 2024
** B-CPE-100-LYN-1-1-cpoolday04-iuliia.dabizha
** File description:
** my_getnbr
*/

#include <stdio.h>

int my_getnbr(char const *str)
{
    long num = 0;
    int s = 1;
    int i = 0;

    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-') {
            s *= -1;
        }
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        num = num * 10 + (str[i] - '0');
        if (num * s > 2147483647 || num * s < -2147483648) {
            return 0;
        }
        i++;
    }
    return (int)(num * s);
}
