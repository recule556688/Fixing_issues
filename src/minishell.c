/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell1-luca.grange
** File description:
** Main minishell file
*/

#include "../includes/my.h"

const builtin_cmd_t BUILTINS[] = {
    {"cd", &builtin_cd},
    {"env", &builtin_env},
    {"setenv", &builtin_setenv},
    {"unsetenv", &builtin_unsetenv},
    {"exit", &builtin_exit},
    {NULL, NULL}
};

static int execute_builtin(char **args, shell_t *shell)
{
    for (int i = 0; BUILTINS[i].name; i++) {
        if (my_strcmp(args[0], BUILTINS[i].name) == 0)
            return BUILTINS[i].func(args, &shell->env);
    }
    return -1;
}

static void handle_child_process(char **args, shell_t *shell)
{
    if (execute_external(args, shell->env) == -1) {
        write(2, args[0], my_strlen(args[0]));
        write(2, ": Command not found.\n", 21);
        exit(1);
    }
}

// This function is kept for backward compatibility, used for simple commands
static void process_command(char **args, shell_t *shell)
{
    pid_t pid;
    int status;

    if (execute_builtin(args, shell) != -1)
        return;
    pid = fork();
    if (pid < 0) {
        perror("fork");
    }
    if (pid == 0) {
        handle_child_process(args, shell);
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            shell->last_exit_status = WEXITSTATUS(status);
    }
}

static void process_input_line(char *line, shell_t *shell)
{
    command_list_t *cmd_list;

    if (line[0] == '\0')
        return;
    cmd_list = parse_input(line);
    if (cmd_list) {
        execute_command_list(cmd_list, shell);
        free_command_list(cmd_list);
    }
}

static void cleanup_shell(shell_t *shell)
{
    for (int i = 0; shell->env[i]; i++)
        free(shell->env[i]);
    free(shell->env);
}

static void run_shell_loop(shell_t *shell)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_chars;

    while (1) {
        if (isatty(0))
            write(1, "$> ", 3);
        read_chars = getline(&line, &len, stdin);
        if (read_chars == -1) {
            free(line);
            break;
        }
        if (read_chars > 0 && line[read_chars - 1] == '\n')
            line[read_chars - 1] = '\0';
        process_input_line(line, shell);
        free(line);
        line = NULL;
    }
}

int main(int argc, char **argv, char **envp)
{
    shell_t shell = {
        .env = copy_env(envp),
        .last_exit_status = 0
    };

    (void)argc;
    (void)argv;
    run_shell_loop(&shell);
    cleanup_shell(&shell);
    if (shell.last_exit_status > 128)
        return 1;
    return shell.last_exit_status;
}
