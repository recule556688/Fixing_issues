/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha (Copy)
** File description:
** parse_format
*/

#include "my.h"
#include "struct.h"

static void init_format_spec(format_spec_t *spec)
{
    spec->width = 0;
    spec->precision = -1;
    spec->zero_pad = 0;
    spec->left_align = 0;
    spec->plus_sign = 0;
    spec->specifier = 0;
}

static int is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static int parse_number(const char **format)
{
    int num = 0;

    while (is_digit(**format)) {
        num = num * 10 + (**format - '0');
        (*format)++;
    }
    return num;
}

static void parse_flags(const char **format, format_spec_t *spec)
{
    while (**format == '-' || **format == '0' || **format == '+') {
        if (**format == '-')
            spec->left_align = 1;
        if (**format == '0' && !spec->left_align)
            spec->zero_pad = 1;
        if (**format == '+')
            spec->plus_sign = 1;
        (*format)++;
    }
}

format_spec_t parse_format_spec(const char **format)
{
    format_spec_t spec;

    init_format_spec(&spec);
    parse_flags(format, &spec);
    if (is_digit(**format))
        spec.width = parse_number(format);
    if (**format == '.') {
        (*format)++;
        spec.precision = parse_number(format);
    }
    spec.specifier = **format;
    (*format)++;
    return spec;
}
