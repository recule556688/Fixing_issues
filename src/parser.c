/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-luca.grange
** File description:
** Command parsing functions
*/

#include "../includes/my.h"
#include <stdbool.h>

static void process_redirection(command_t *cmd, char **tokens, int *index)
{
    char *op = tokens[*index];

    (*index)++;
    if (!tokens[*index]) {
        write(2, REDIR_ERR_MSG, sizeof(REDIR_ERR_MSG));
        return;
    }
    if (my_strcmp(op, "<") == 0) {
        cmd->input_file = my_strdup(tokens[*index]);
    }
    if (my_strcmp(op, ">") == 0) {
        cmd->output_file = my_strdup(tokens[*index]);
        cmd->append_output = false;
    }
    if (my_strcmp(op, ">>") == 0) {
        cmd->output_file = my_strdup(tokens[*index]);
        cmd->append_output = true;
    }
    (*index)++;
}

static void handle_pipe(command_t *cmd, int *index)
{
    (*index)++;
    cmd->next = create_command();
}

static void add_arg_to_command(command_t *cmd, char *arg)
{
    int i = 0;

    while (cmd->args[i])
        i++;
    cmd->args[i] = my_strdup(arg);
    cmd->args[i + 1] = NULL;
}

static void handle_redirect_token(command_t **current_cmd,
    char **tokens, int *i)
{
    if (my_strcmp(tokens[*i], "|") == 0) {
        handle_pipe(*current_cmd, i);
        *current_cmd = (*current_cmd)->next;
        return;
    }
    process_redirection(*current_cmd, tokens, i);
}

static void process_command_tokens(command_t *current_cmd,
    char **tokens, int *i)
{
    while (tokens[*i] && my_strcmp(tokens[*i], ";") != 0) {
        if (is_redirect_token(tokens[*i])) {
            handle_redirect_token(&current_cmd, tokens, i);
        } else {
            add_arg_to_command(current_cmd, tokens[*i]);
            (*i)++;
        }
    }
}

static command_t *parse_pipeline(char **tokens, int *index)
{
    command_t *pipeline = create_command();
    command_t *current_cmd = pipeline;
    int i = *index;

    process_command_tokens(current_cmd, tokens, &i);
    *index = i;
    return pipeline;
}

static void handle_semicolon(command_list_t **current_list, char **tokens,
    int *i)
{
    if (!tokens[*i] || my_strcmp(tokens[*i], ";") != 0)
        return;
    (*i)++;
    if (!tokens[*i])
        return;
    (*current_list)->next = create_command_list();
    *current_list = (*current_list)->next;
}

command_list_t *parse_input(char *input)
{
    char **tokens = tokenize_input(input);
    command_list_t *cmd_list = create_command_list();
    command_list_t *current_list = cmd_list;
    int i = 0;

    while (tokens[i]) {
        current_list->first = parse_pipeline(tokens, &i);
        handle_semicolon(&current_list, tokens, &i);
    }
    free(tokens);
    return cmd_list;
}
