/*
** EPITECH PROJECT, 2025
** Fixing_issues
** File description:
** parser_utilis
*/

#include "../includes/my.h"

void free_command(command_t *cmd)
{
    command_t *next;
    int i;

    while (cmd) {
        next = cmd->next;
        i = 0;
        while (cmd->args[i]) {
            free(cmd->args[i]);
            i++;
        }
        free(cmd->args);
        if (cmd->input_file)
            free(cmd->input_file);
        if (cmd->output_file)
            free(cmd->output_file);
        free(cmd);
        cmd = next;
    }
}

void free_command_list(command_list_t *list)
{
    command_list_t *next;

    while (list) {
        next = list->next;
        free_command(list->first);
        free(list);
        list = next;
    }
}
