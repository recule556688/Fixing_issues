/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-miniprintf-luca.grange
** File description:
** mini_printf
*/

#include "my.h"

static int handle_percent(const char **s_ptr, va_list ap)
{
    format_spec_t spec;

    if (**s_ptr == '\0')
        return 0;
    spec = parse_format_spec(s_ptr);
    if (spec.specifier == 'd' || spec.specifier == 'i'
        || spec.specifier == 'u' || spec.specifier == 'f')
        return handle_numeric_flags(spec, ap);
    if (spec.specifier == 'x' || spec.specifier == 'X'
        || spec.specifier == 'p')
        return print_flags_hexa(ap, spec);
    if (spec.specifier == 'c' || spec.specifier == 's')
        return print_flags_char(ap, spec);
    if (spec.specifier == 'o' || spec.specifier == 'b')
        return print_flags_octal_or_binary(ap, spec);
    if (spec.specifier == '%') {
        my_putchar('%');
        return 1;
    }
    return 0;
}

int my_printf(const char *format, ...)
{
    va_list ap;
    int count = 0;

    if (!format)
        return 0;
    va_start(ap, format);
    while (*format) {
        if (*format == '%') {
            format++;
            count += handle_percent(&format, ap);
        } else {
            my_putchar(*format);
            count++;
            format++;
        }
    }
    va_end(ap);
    return count;
}
