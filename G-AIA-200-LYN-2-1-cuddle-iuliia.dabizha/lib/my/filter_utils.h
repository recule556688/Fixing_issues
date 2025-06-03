/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** filter_utils
*/

#ifndef FILTER_UTILS_H_
    #define FILTER_UTILS_H_

    #include "dataframe.h"

void *copy_column_value(void *value, char type);
dataframe_t *init_filtered_dataframe(dataframe_t *src);
int find_column_index(dataframe_t *dataframe, const char *column_name);

#endif /* !FILTER_UTILS_H_ */
