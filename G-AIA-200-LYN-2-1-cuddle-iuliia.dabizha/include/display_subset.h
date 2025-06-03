/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** display_subset - Header for subset display functions
*/

#ifndef DISPLAY_SUBSET_H_
    #define DISPLAY_SUBSET_H_

    #include "dataframe.h"

dataframe_t *df_head(dataframe_t *dataframe, int nb_rows);
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows);

#endif /* !DISPLAY_SUBSET_H_ */
