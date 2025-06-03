/*
** EPITECH PROJECT, 2024
** B-CPE-100-LYN-1-1-cpoolday06-iuliia.dabizha
** File description:
** my_strcpy
*/

#include <stdio.h>

char *my_strcpy(char *dest, char const *src)
{
    int i;

    for (i = 0; src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}
