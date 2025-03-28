/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-luca.grange
** File description:
** Execute utility functions
*/

#include "../includes/my.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int run_redirected_builtin(command_t *cmd, shell_t *shell,
    int input_fd, int output_fd)
{
    int stdin_backup = backup_fd(input_fd, STDIN_FILENO);
    int stdout_backup = backup_fd(output_fd, STDOUT_FILENO);
    int result = 0;

    for (int i = 0; BUILTINS[i].name; i++) {
        if (my_strcmp(cmd->args[0], BUILTINS[i].name) == 0) {
            result = BUILTINS[i].func(cmd->args, &shell->env);
            break;
        }
    }
    restore_fd(stdin_backup, STDIN_FILENO);
    restore_fd(stdout_backup, STDOUT_FILENO);
    return result;
}

static int check_if_exit(command_t *cmd, shell_t *shell)
{
    for (int i = 0; BUILTINS[i].name; i++) {
        if (my_strcmp(cmd->args[0], "exit") == 0 &&
            my_strcmp(BUILTINS[i].name, "exit") == 0)
            return BUILTINS[i].func(cmd->args, &shell->env);
    }
    return -1;
}

int handle_builtin(command_t *cmd, shell_t *shell,
    int input_fd, int output_fd)
{
    int exit_result = check_if_exit(cmd, shell);

    if (exit_result != -1)
        return exit_result;
    for (int i = 0; BUILTINS[i].name; i++) {
        if (my_strcmp(cmd->args[0], BUILTINS[i].name) == 0)
            return run_redirected_builtin(cmd, shell, input_fd, output_fd);
    }
    return -1;
}

void run_child_task(command_t *cmd, shell_t *shell,
    int input_fd, int output_fd)
{
    if (input_fd != STDIN_FILENO) {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (output_fd != STDOUT_FILENO) {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }
    if (execute_external(cmd->args, shell->env) == -1) {
        write(2, cmd->args[0], my_strlen(cmd->args[0]));
        write(2, COMMAND_NOT_FOUND_MSG, sizeof(COMMAND_NOT_FOUND_MSG));
        exit(1);
    }
    exit(0);
}
