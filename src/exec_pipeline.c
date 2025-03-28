/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-luca.grange
** File description:
** Pipeline and redirection execution
*/

#include "../includes/my.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

static int wait_for_process(pid_t pid)
{
    int status;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return 1;
}

static int run_parent_task(command_t *cmd, shell_t *shell,
    int input_fd, int output_fd)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        run_child_task(cmd, shell, input_fd, output_fd);
    }
    close_if_not_default(input_fd, output_fd);
    return wait_for_process(pid);
}

int execute_command(command_t *cmd, shell_t *shell,
    int input_fd, int output_fd)
{
    int result = 0;

    if (!cmd->args[0])
        return 0;
    result = handle_builtin(cmd, shell, input_fd, output_fd);
    if (result != -1)
        return result;
    return run_parent_task(cmd, shell, input_fd, output_fd);
}

static int setup_pipe(int pipe_fds[2])
{
    if (pipe(pipe_fds) == -1) {
        perror("pipe");
        return 0;
    }
    return 1;
}

static int handle_pipe_output(int pipe_fds[2], int *output_fd)
{
    if (!setup_pipe(pipe_fds))
        return 0;
    *output_fd = pipe_fds[1];
    return 1;
}

static int handle_file_output(command_t *cmd, int *output_fd)
{
    *output_fd = handle_output_redirection(cmd);
    return (*output_fd != -1);
}

static int setup_output(command_t *cmd, int *output_fd, int pipe_fds[2])
{
    if (cmd->next)
        return handle_pipe_output(pipe_fds, output_fd);
    if (cmd->output_file)
        return handle_file_output(cmd, output_fd);
    *output_fd = STDOUT_FILENO;
    return 1;
}

static int process_command(command_t *cmd, shell_t *shell,
    int *input_fd, int pipe_fds[2])
{
    int output_fd = STDOUT_FILENO;
    int status;

    if (!setup_output(cmd, &output_fd, pipe_fds))
        return 1;
    status = execute_command(cmd, shell, *input_fd, output_fd);
    if (cmd->next)
        *input_fd = pipe_fds[0];
    return status;
}

int execute_pipeline(command_t *pipeline, shell_t *shell)
{
    int status = 0;
    int pipe_fds[2];
    command_t *current = pipeline;
    int input_fd = STDIN_FILENO;

    if (current->input_file) {
        input_fd = handle_input_redirection(current);
        if (input_fd == -1)
            return 1;
    }
    while (current) {
        status = process_command(current, shell, &input_fd, pipe_fds);
        current = current->next;
    }
    return status;
}

int execute_command_list(command_list_t *cmd_list, shell_t *shell)
{
    command_list_t *current = cmd_list;
    int status = 0;

    while (current) {
        status = execute_pipeline(current->first, shell);
        shell->last_exit_status = status;
        current = current->next;
    }
    return status;
}
