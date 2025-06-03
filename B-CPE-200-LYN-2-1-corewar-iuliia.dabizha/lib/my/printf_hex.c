/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha (Copy)
** File description:
** printf_hex
*/

#include "my.h"

static int handle_hex_padding(unsigned int num, char *base, format_spec_t spec)
{
    int total = 0;
    int len = 0;
    unsigned int temp = num;

    do {
        len++;
        temp /= 16;
    } while (temp);
    if (!spec.left_align && spec.width > len) {
        total += print_padding(spec.width - len, 0, spec.zero_pad);
    }
    total += my_put_unsigned_nbr_base(num, base);
    if (spec.left_align && spec.width > len) {
        total += print_padding(spec.width - len, 0, 0);
    }
    return total;
}

int print_flags_hexa(va_list list, format_spec_t spec)
{
    unsigned int num;

    switch (spec.specifier) {
        case 'x':
            num = va_arg(list, unsigned int);
            return handle_hex_padding(num, HEXA_LOW, spec);
        case 'X':
            num = va_arg(list, unsigned int);
            return handle_hex_padding(num, HEXA_UP, spec);
        case 'p':
            return handle_pointer(va_arg(list, unsigned long long));
        default:
            return 0;
    }
}

int print_flags_octal_or_binary(va_list list, format_spec_t spec)
{
    unsigned int arg = va_arg(list, unsigned int);

    switch (spec.specifier) {
        case 'o':
            return my_put_unsigned_nbr_base(arg, OCTAL);
        case 'b':
            return my_put_unsigned_nbr_base(arg, BINARY);
        default:
            return 0;
    }
}
