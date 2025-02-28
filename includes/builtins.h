/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell1-luca.grange
** File description:
** Builtin commands
*/

#ifndef BUILTINS_H_
    #define BUILTINS_H_

typedef struct builtin_cmd_s {
    const char *name;
    int (*func)(char **args, char ***env);
} builtin_cmd_t;

int builtin_cd(char **args, char ***env);
int builtin_env(char **args, char ***env);
int builtin_setenv(char **args, char ***env);
int builtin_unsetenv(char **args, char ***env);
int builtin_exit(char **args, char ***env);

#endif /* !BUILTINS_H_ */
