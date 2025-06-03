/*
** EPITECH PROJECT, 2024
** B-CPE-101-LYN-1-1-myprintf-iuliia.dabizha (Copy)
** File description:
** struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

typedef struct format_spec {
    int width;          // Minimum field width
    int precision;      // Precision for floats/strings
    int zero_pad;       // Should we pad with zeros?
    int left_align;     // Should we left-align?
    int plus_sign;      // Should we add a plus sign?
    char specifier;     // The actual format specifier (d,f,s etc)
} format_spec_t;
#endif /* !STRUCT_H_ */
