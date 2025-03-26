/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-luca.grange
** File description:
** Command parsing functions
*/

#include "../includes/my.h"
#include <stdbool.h>

static bool is_redirect_token(const char *token)
{
    return (my_strcmp(token, "<") == 0 || my_strcmp(token, ">") == 0 ||
        my_strcmp(token, ">>") == 0 || my_strcmp(token, "|") == 0);
}

static void init_command(command_t *cmd)
{
    cmd->args = malloc(sizeof(char *) * MAX_TOKENS);
    if (!cmd->args) {
        write(2, "Error: malloc failed\n", 21);
        exit(84);
    }
    cmd->args[0] = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append_output = false;
    cmd->next = NULL;
}

static command_t *create_command(void)
{
    command_t *cmd = malloc(sizeof(command_t));

    if (!cmd) {
        write(2, "Error: malloc failed\n", 21);
        exit(84);
    }
    init_command(cmd);
    return cmd;
}

static command_list_t *create_command_list(void)
{
    command_list_t *list = malloc(sizeof(command_list_t));

    if (!list) {
        write(2, "Error: malloc failed\n", 21);
        exit(84);
    }
    list->first = create_command();
    list->next = NULL;
    return list;
}

static void process_redirection(command_t *cmd, char **tokens, int *index)
{
    char *op = tokens[*index];

    (*index)++;
    if (!tokens[*index]) {
        write(2, "Syntax error: missing filename after redirection\n", 48);
        return;
    }
    if (my_strcmp(op, "<") == 0) {
        cmd->input_file = my_strdup(tokens[*index]);
    } else if (my_strcmp(op, ">") == 0) {
        cmd->output_file = my_strdup(tokens[*index]);
        cmd->append_output = false;
    } else if (my_strcmp(op, ">>") == 0) {
        cmd->output_file = my_strdup(tokens[*index]);
        cmd->append_output = true;
    }
    (*index)++;
}

static void handle_pipe(command_t *cmd, char **tokens, int *index)
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

static command_t *parse_pipeline(char **tokens, int *index)
{
    command_t *pipeline = create_command();
    command_t *current_cmd = pipeline;
    int i = *index;

    while (tokens[i] && my_strcmp(tokens[i], ";") != 0) {
        if (is_redirect_token(tokens[i])) {
            if (my_strcmp(tokens[i], "|") == 0) {
                handle_pipe(current_cmd, tokens, &i);
                current_cmd = current_cmd->next;
            } else {
                process_redirection(current_cmd, tokens, &i);
            }
        } else {
            add_arg_to_command(current_cmd, tokens[i]);
            i++;
        }
    }
    *index = i;
    return pipeline;
}

static char **tokenize_input(char *input)
{
    char **tokens = malloc(sizeof(char *) * MAX_TOKENS);
    char *token;
    int count = 0;

    if (!tokens) {
        write(2, "Error: malloc failed\n", 21);
        exit(84);
    }
    token = strtok(input, " \t\n");
    while (token && count < MAX_TOKENS - 1) {
        tokens[count++] = token;
        token = strtok(NULL, " \t\n");
    }
    tokens[count] = NULL;
    return tokens;
}

command_list_t *parse_input(char *input)
{
    char **tokens = tokenize_input(input);
    command_list_t *cmd_list = create_command_list();
    command_list_t *current_list = cmd_list;
    int i = 0;

    while (tokens[i]) {
        current_list->first = parse_pipeline(tokens, &i);
        if (tokens[i] && my_strcmp(tokens[i], ";") == 0) {
            i++;
            if (tokens[i]) {
                current_list->next = create_command_list();
                current_list = current_list->next;
            }
        }
    }
    free(tokens);
    return cmd_list;
}

static void free_command(command_t *cmd)
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
