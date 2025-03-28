/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-luca.grange
** File description:
** Pipeline utility functions
*/

#include "../includes/my.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int handle_input_redirection(command_t *cmd)
{
    int fd;

    if (cmd->input_file) {
        fd = open(cmd->input_file, O_RDONLY);
        if (fd == -1) {
            write(2, cmd->input_file, my_strlen(cmd->input_file));
            write(2, NO_SUCH_FILE_MSG, sizeof(NO_SUCH_FILE_MSG));
            return -1;
        }
        return fd;
    }
    return STDIN_FILENO;
}

int handle_output_redirection(command_t *cmd)
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

int backup_fd(int new_fd, int original_fd)
{
    int backup = -1;

    if (new_fd != original_fd) {
        backup = dup(original_fd);
        dup2(new_fd, original_fd);
    }
    return backup;
}

void restore_fd(int backup_fd, int original_fd)
{
    if (backup_fd != -1) {
        dup2(backup_fd, original_fd);
        close(backup_fd);
    }
}

void close_if_not_default(int input_fd, int output_fd)
{
    if (input_fd != STDIN_FILENO)
        close(input_fd);
    if (output_fd != STDOUT_FILENO)
        close(output_fd);
}
