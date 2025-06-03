/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha (Copy)
** File description:
** printf_numeric
*/

#include "my.h"

static void handle_sign_output(int is_negative, int plus_sign)
{
    my_putchar(is_negative ? '-' : '+');
}

static int handle_zero_padding(int width, int len, int is_negative,
    int plus_sign)
{
    int total = 0;

    if (is_negative || plus_sign) {
        handle_sign_output(is_negative, plus_sign);
        total++;
        total += print_padding(width - 1, len - 1, 1);
    } else {
        total += print_padding(width, len, 1);
    }
    return total;
}

static int handle_regular_padding(int width, int len, int is_negative,
    int plus_sign)
{
    int total = 0;

    total += print_padding(width, len, 0);
    if (is_negative || plus_sign) {
        handle_sign_output(is_negative, plus_sign);
        total++;
    }
    return total;
}

static int handle_left_aligned(int num, int len, int total, format_spec_t spec)
{
    int is_negative = num < 0;

    if (is_negative || (spec.plus_sign && num >= 0)) {
        handle_sign_output(is_negative, spec.plus_sign);
        total++;
    }
    my_put_nbr(is_negative ? - num : num);
    total += len - (is_negative || (spec.plus_sign && num >= 0) ? 1 : 0);
    if (spec.width > len)
        total += print_padding(spec.width, len, 0);
    return total;
}

static int handle_right_aligned(int num, int len, int total,
    format_spec_t spec)
{
    int is_negative = num < 0;

    if (spec.width > len) {
        total += spec.zero_pad ?
            handle_zero_padding(spec.width, len, is_negative, spec.plus_sign) :
            handle_regular_padding(spec.width, len, is_negative,
                spec.plus_sign);
    } else if (is_negative || (spec.plus_sign && num >= 0)) {
        handle_sign_output(is_negative, spec.plus_sign);
        total++;
    }
    my_put_nbr(is_negative ? - num : num);
    total += len - (is_negative || (spec.plus_sign && num >= 0) ? 1 : 0);
    return total;
}

int handle_integer_flags(va_list list, format_spec_t spec)
{
    int num = va_arg(list, int);
    int len = num_char_in_int(num);
    int total = 0;
    int is_negative = (num < 0);

    if ((spec.plus_sign && num >= 0) || is_negative)
        len++;
    return spec.left_align ?
        handle_left_aligned(num, len, total, spec)
        : handle_right_aligned(num, len, total, spec);
}

int handle_numeric_flags(format_spec_t spec, va_list ap)
{
    switch (spec.specifier) {
        case 'd':
        case 'i':
            return handle_integer_flags(ap, spec);
        case 'u':
            return handle_unsigned_int(ap);
        case 'f':
            return my_putfloat(va_arg(ap, double), spec.precision, spec);
        default:
            return 0;
    }
}
