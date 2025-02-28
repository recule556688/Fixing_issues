/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell1-luca.grange
** File description:
** Main minishell header
*/

#ifndef MINISHELL_H_
    #define MINISHELL_H_

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <signal.h>
    #include <sys/types.h>
    #include <string.h>

    #include "my_string.h"
    #include "builtins.h"
    #include "env.h"
    #include "exec.h"

    #define MAX_TOKENS 128

typedef struct shell_s {
    char **env;
    int last_exit_status;
} shell_t;

// String manipulation functions
size_t my_strlen(const char *str);
char *my_strdup(const char *str);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, int n);
char *my_strchr(const char *s, int c);

// Built-in commands
int builtin_cd(char **args, char ***env);
int builtin_env(char **args, char ***env);
int builtin_setenv(char **args, char ***env);
int builtin_unsetenv(char **args, char ***env);
int builtin_exit(char **args, char ***env);

// Command execution
int execute_external(char **args, char **env);
int try_path_search(char **args, char *path_env);

#endif /* !MINISHELL_H_ */
