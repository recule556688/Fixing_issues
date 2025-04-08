/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** Write a string to stdout
*/

void my_putchar(char c);

void my_putstr(const char *str)
{
    if (!str)
        return;
    while (*str) {
        my_putchar(*str);
        str++;
    }
} 