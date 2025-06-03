/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** my_atoi
*/

#include <stdbool.h>

int my_atoi(const char *str)
{
    int result = 0;
    int sign = 1;

    while (*str == ' ' || *str == '\t' || *str == '\n' ||
        *str == '\r' || *str == '\v' || *str == '\f') {
        str++;
    }
    if (*str == '-' || *str == '+') {
        if (*str == '-') {
            sign = -1;
        }
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}
