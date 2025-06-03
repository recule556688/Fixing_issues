/*
** EPITECH PROJECT, 2024
** B-CPE-100-LYN-1-1-cpoolday06-luca.grange
** File description:
** include
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>
#include "struct.h"

#ifndef MY_H
    #define MY_H
    #define BUFFER_SIZE 30720
    #define BINARY "01"
    #define OCTAL "01234567"
    #define HEXA_LOW "0123456789abcdef"
    #define HEXA_UP "0123456789ABCDEF"

int my_getnbr(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
int my_strcmp(char const *s1, char const *s2);
void my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_printf(const char *format, ...);
int my_putfloat(double nb, int precision, format_spec_t spec);
int my_put_unsigned_nbr(unsigned int nb);
int my_put_unsigned_nbr_base(unsigned int nbr, char const *base);
int handle_unsigned_int_hexa(va_list list, char *base);
int handle_pointer(unsigned long long arg);
int handle_unsigned_int_octal(va_list list);
int handle_unsigned_int(va_list list);
int handle_int(va_list list);
int handle_float(va_list list);
int handle_char(va_list list);
int handle_string(va_list list);
int my_put_pointer_nbr_base(unsigned long long nbr, char const *base);
int num_char_in_int(int n);
int num_char_in_uint(unsigned int n);
int print_specials(char specifier);
int print_flags_int(va_list list, format_spec_t spec);
int print_flags_char(va_list list, format_spec_t spec);
int print_flags_hexa(va_list list, format_spec_t spec);
int print_flags_octal_or_binary(va_list list, format_spec_t spec);
format_spec_t parse_format_spec(const char **s_ptr);
int print_padding(int width, int content_len, int zero_pad);
int handle_numeric_flags(format_spec_t spec, va_list ap);
int handle_hex_pointer_flags(format_spec_t spec, va_list ap);
long long my_dec_pow(int exp);
void *my_memcpy(void *dest, const void *src, size_t n);
int my_atoi(const char *str);

#endif // MY_H_
