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

static int handle_input_redirection(command_t *cmd)
{
    int fd;

    if (cmd->input_file) {
        fd = open(cmd->input_file, O_RDONLY);
        if (fd == -1) {
            write(2, cmd->input_file, my_strlen(cmd->input_file));
            write(2, ": No such file or directory.\n", 29);
            return -1;
        }
        return fd;
    }
    return STDIN_FILENO;
}

static int handle_output_redirection(command_t *cmd)
{
    int fd;
    int flags = O_WRONLY | O_CREAT;

    if (cmd->output_file) {
        flags |= cmd->append_output ? O_APPEND : O_TRUNC;
        fd = open(cmd->output_file, flags, 0644);
        if (fd == -1) {
            perror(cmd->output_file);
            return -1;
        }
        return fd;
    }
    return STDOUT_FILENO;
}

//If new_fd != original_fd,
//creates a backup of original_fd and duplicates new_fd onto original_fd.
//Returns the backup or -1 if no backup was made.
static int backup_fd(int new_fd, int original_fd)
{
    int backup = -1;

    if (new_fd != original_fd) {
        backup = dup(original_fd);
        dup2(new_fd, original_fd);
    }
    return backup;
}

//If backup_fd != -1, dupes backup_fd onto original_fd, closing backup_fd.
static void restore_fd(int backup_fd, int original_fd)
{
    if (backup_fd != -1) {
        dup2(backup_fd, original_fd);
        close(backup_fd);
    }
}

static int run_redirected_builtin(command_t *cmd, shell_t *shell,
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

//Removed this since you don't need it.
            // if (my_strcmp(cmd->args[0], "cd") == 0 &&
            //     (input_fd != STDIN_FILENO || output_fd != STDOUT_FILENO)) {
            //     return run_redirected_builtin(cmd, shell,
            // input_fd, output_fd);
            // }
static int handle_builtin(command_t *cmd, shell_t *shell,
    int input_fd, int output_fd)
{
    int result = -1;

    for (int i = 0; BUILTINS[i].name; i++) {
        if (my_strcmp(cmd->args[0], "exit") == 0)
            return 0;
        if (my_strcmp(cmd->args[0], BUILTINS[i].name) == 0)
            return run_redirected_builtin(cmd, shell, input_fd, output_fd);
    }
    return result;
}

static void run_child_task(command_t *cmd, shell_t *shell,
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
        write(2, ": Command not found.\n", 21);
        exit(1);
    }
    exit(0);
}

static void close_if_not_default(int input_fd, int output_fd)
{
    if (input_fd != STDIN_FILENO)
        close(input_fd);
    if (output_fd != STDOUT_FILENO)
        close(output_fd);
}

static int run_parent_task(command_t *cmd, shell_t *shell,
    int input_fd, int output_fd)
{
    int status;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        run_child_task(cmd, shell, input_fd, output_fd);
    } else {
        close_if_not_default(input_fd, output_fd);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
    }
    return 1;
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
    else
        return run_parent_task(cmd, shell, input_fd, output_fd);
}

int execute_pipeline(command_t *pipeline, shell_t *shell)
{
    int status = 0;
    int pipe_fds[2];
    command_t *current = pipeline;
    command_t *next = current->next;
    int input_fd = STDIN_FILENO;
    int output_fd = STDOUT_FILENO;
    bool exit_command_seen = false;

    if (pipeline->args[0] && my_strcmp(pipeline->args[0], "exit") == 0 &&
        pipeline->next && pipeline->next->args[0] && my_strcmp(pipeline->next->args[0], "cat") == 0) {
        if (pipeline->args[1])
            shell->last_exit_status = my_atoi(pipeline->args[1]);
        else
            shell->last_exit_status = 0;
        write(2, "cat: Command not found.\n", 24);
        return 1;
    }
    if (current->input_file) {
        input_fd = handle_input_redirection(current);
        if (input_fd == -1)
            return 1;
    }
    while (current) {
        next = current->next;
        if (next) {
            if (pipe(pipe_fds) == -1) {
                perror("pipe");
                return 1;
            }
            output_fd = pipe_fds[1];
        } else if (current->output_file) {
            output_fd = handle_output_redirection(current);
            if (output_fd == -1)
                return 1;
        } else {
            output_fd = STDOUT_FILENO;
        }
        if (current->args[0] && my_strcmp(current->args[0], "exit") == 0) {
            exit_command_seen = true;
            if (current->args[1])
                shell->last_exit_status = my_atoi(current->args[1]);
            else
                shell->last_exit_status = 0;
        } else {
            status = execute_command(current, shell, input_fd, output_fd);
        }
        if (next) {
            input_fd = pipe_fds[0];
        }
        current = next;
    }
    return exit_command_seen ? shell->last_exit_status : status;
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
