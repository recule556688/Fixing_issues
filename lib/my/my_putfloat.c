/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha
** File description:
** my_putfloat
*/

#include "my.h"

static void print_separated_float(long long nb, int precision)
{
    my_put_nbr(nb / my_dec_pow(precision));
    my_putchar('.');
    my_put_nbr(nb % my_dec_pow(precision));
}

static int print_decimal_part(double nb, int precision)
{
    double dec_part;
    int total = 1;
    int digit;
    long long multiplier = 1;

    my_putchar('.');
    dec_part = nb - (long long)nb;
    if (dec_part < 0)
        dec_part = -dec_part;
    for (int i = 0; i < precision; i++) {
        multiplier *= 10;
        digit = (int)((dec_part * multiplier) - ((long long)(dec_part *
            (multiplier / 10)) * 10));
        my_putchar('0' + digit);
        total++;
    }
    return total;
}

static void handle_sign(int is_negative, int plus_sign)
{
    my_putchar(is_negative ? '-' : '+');
}

static int handle_padding(int width, int full_len, int zero_pad)
{
    return print_padding(width, full_len, zero_pad);
}

static int handle_left_padding(format_spec_t spec, int full_len,
    int is_negative)
{
    int total = 0;

    if (spec.zero_pad) {
        if (is_negative || spec.plus_sign) {
            handle_sign(is_negative, spec.plus_sign);
            total++;
            total += handle_padding(spec.width - 1, full_len - 1, 1);
        } else {
            total += handle_padding(spec.width, full_len, 1);
        }
        return total;
    }
    total += handle_padding(spec.width, full_len, 0);
    if (is_negative || spec.plus_sign) {
        handle_sign(is_negative, spec.plus_sign);
        total++;
    }
    return total;
}

int my_putfloat(double nb, int precision, format_spec_t spec)
{
    int len = num_char_in_int((int)nb);
    int actual_precision = precision >= 0 ? precision : 6;
    int dec_len = actual_precision + 1;
    int is_negative = nb < 0;
    int full_len = len + dec_len + (is_negative || spec.plus_sign ? 1 : 0);
    int total = full_len;
    long long rest;

    if (!spec.left_align && spec.width > full_len)
        total += handle_left_padding(spec, full_len, is_negative);
    else if (is_negative || spec.plus_sign) {
        handle_sign(is_negative, spec.plus_sign);
        total++;
    }
    rest = (long long) (nb * my_dec_pow(dec_len));
    rest = (rest + (rest % 10 >= 5)) / 10;
    print_separated_float(rest, actual_precision);
    if (spec.left_align && spec.width > full_len)
        total += handle_padding(spec.width, full_len, 0);
    return total;
}
