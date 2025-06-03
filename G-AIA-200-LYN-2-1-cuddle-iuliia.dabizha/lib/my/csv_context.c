/*
** EPITECH PROJECT, 2025
** G-AIA-200-LYN-2-1-cuddle-iuliia.dabizha
** File description:
** csv_context
*/

#include "dataframe.h"
#include "dataframe_utils.h"
#include "struct.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cleanup_csv_context(csv_context_t *ctx, dataframe_t *df)
{
    if (ctx->file)
        fclose(ctx->file);
    if (ctx->line)
        free(ctx->line);
    if (df)
        df_free(df);
}

bool init_csv_context(csv_context_t *ctx, const char *filename)
{
    ctx->file = fopen(filename, "r");
    ctx->line = NULL;
    ctx->len = 0;
    ctx->col_count = 0;
    return ctx->file != NULL;
}
