/*
** EPITECH PROJECT, 2025
** my_putfloat
** File description:
** Write a float to stdout with precision
*/

void my_putchar(char c);
void my_putstr(const char *str);

static void put_number(int n)
{
    if (n < 0) {
        my_putchar('-');
        n = -n;
    }
    if (n >= 10)
        put_number(n / 10);
    my_putchar(n % 10 + '0');
}

void my_putfloat(float num, int precision)
{
    int integer_part = (int)num;
    float decimal_part = num - integer_part;
    int i;

    put_number(integer_part);
    my_putchar('.');
    for (i = 0; i < precision; i++) {
        decimal_part *= 10;
        my_putchar((int)decimal_part % 10 + '0');
    }
} 