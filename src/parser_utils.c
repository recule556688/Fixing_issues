/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-luca.grange
** File description:
** Parser utility functions
*/

#include "../includes/my.h"
#include <stdbool.h>

bool is_redirect_token(const char *token)
{
    return (my_strcmp(token, "<") == 0 || my_strcmp(token, ">") == 0 ||
        my_strcmp(token, ">>") == 0 || my_strcmp(token, "|") == 0);
}

static void init_command(command_t *cmd)
{
    cmd->args = malloc(sizeof(char *) * MAX_COMMAND_TOKENS);
    if (!cmd->args) {
        write(2, MALLOC_ERR_MSG, sizeof(MALLOC_ERR_MSG));
        exit(84);
    }
    cmd->args[0] = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append_output = false;
    cmd->next = NULL;
}

command_t *create_command(void)
{
    command_t *cmd = malloc(sizeof(command_t));

    if (!cmd) {
        write(2, MALLOC_ERR_MSG, sizeof(MALLOC_ERR_MSG));
        exit(84);
    }
    init_command(cmd);
    return cmd;
}

command_list_t *create_command_list(void)
{
    command_list_t *list = malloc(sizeof(command_list_t));

    if (!list) {
        write(2, MALLOC_ERR_MSG, sizeof(MALLOC_ERR_MSG));
        exit(84);
    }
    list->first = create_command();
    list->next = NULL;
    return list;
}

char **tokenize_input(char *input)
{
    char **tokens = malloc(sizeof(char *) * MAX_COMMAND_TOKENS);
    char *token;
    int count = 0;

    if (!tokens) {
        write(2, MALLOC_ERR_MSG, sizeof(MALLOC_ERR_MSG));
        exit(84);
    }
    token = strtok(input, " \t\n");
    while (token && count < MAX_COMMAND_TOKENS - 1) {
        tokens[count] = token;
        token = strtok(NULL, " \t\n");
        count++;
    }
    tokens[count] = NULL;
    return tokens;
}
