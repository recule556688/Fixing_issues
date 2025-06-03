/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha (Copy)
** File description:
** printf_char
*/

#include "my.h"

static int handle_char_flag(format_spec_t spec, va_list list)
{
    int total = 0;
    char c = va_arg(list, int);

    if (!spec.left_align && spec.width > 0) {
        total += print_padding(spec.width - 1, 0, 0);
    }
    my_putchar(c);
    total++;
    if (spec.left_align && spec.width > 0) {
        total += print_padding(spec.width - 1, 0, 0);
    }
    return total;
}

static int print_string_with_precision(char *str, int len, format_spec_t spec)
{
    int total = 0;
    int pad_width = spec.width > len ? spec.width - len : 0;

    if (!spec.left_align && pad_width > 0)
        total += print_padding(pad_width, 0, 0);
    for (int i = 0; i < len; i++) {
        my_putchar(str[i]);
        total++;
    }
    if (spec.left_align && pad_width > 0)
        total += print_padding(pad_width, 0, 0);
    return total;
}

static int handle_string_flag(format_spec_t spec, va_list list)
{
    char *str = va_arg(list, char *);
    int len;

    if (str == NULL)
        str = "(null)";
    len = my_strlen(str);
    if (spec.precision >= 0 && spec.precision < len)
        len = spec.precision;
    return print_string_with_precision(str, len, spec);
}

int print_flags_char(va_list list, format_spec_t spec)
{
    switch (spec.specifier) {
        case 'c':
            return handle_char_flag(spec, list);
        case 's':
            return handle_string_flag(spec, list);
        default:
            return 0;
    }
}
