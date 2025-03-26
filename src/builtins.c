/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell1-luca.grange
** File description:
** Builtin command functions
*/

#include "../includes/my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int cd_to_home(char ***env)
{
    char *home = get_env_value(*env, "HOME");

    if (!home) {
        write(2, "cd: No HOME variable set.\n", 28);
        return 1;
    }
    if (chdir(home) != 0) {
        perror("cd");
        return 1;
    }
    return 0;
}

int builtin_cd(char **args, char ***env)
{
    if (!args[1])
        return cd_to_home(env);
    if (chdir(args[1]) != 0) {
        perror("cd");
        return 1;
    }
    return 0;
}

int builtin_env(char **args, char ***env)
{
    if (args[1]) {
        write(2, "env: Too many arguments.\n", 26);
        return 1;
    }
    for (int i = 0; (*env)[i]; i++) {
        write(1, (*env)[i], my_strlen((*env)[i]));
        write(1, "\n", 1);
    }
    return 0;
}

static int update_env_var(char ***env, char *var, char *value, int len)
{
    int i = 0;

    for (; (*env)[i]; i++) {
        if (my_strncmp((*env)[i], var, len) == 0 && (*env)[i][len] == '=') {
            free((*env)[i]);
            (*env)[i] = build_var_value(var, value ? value : "");
            return 0;
        }
    }
    return i;
}

static int add_env_var(char ***env, char *var, char *value, int count)
{
    char **new_env = malloc(sizeof(char *) * (count + 2));

    if (!new_env) {
        write(2, "Error: malloc failed\n", 23);
        exit(84);
    }
    for (int j = 0; j < count; j++)
        new_env[j] = (*env)[j];
    new_env[count] = build_var_value(var, value ? value : "");
    new_env[count + 1] = NULL;
    free(*env);
    *env = new_env;
    return 0;
}

int builtin_setenv(char **args, char ***env)
{
    int count;

    if (!args[1])
        return builtin_env(args, env);
    if (args[2] && args[3]) {
        write(2, "setenv: Too many arguments.\n", 27);
        return 1;
    }
    count = update_env_var(env, args[1], args[2], my_strlen(args[1]));
    if (count >= 0)
        return add_env_var(env, args[1], args[2], count);
    return 0;
}

static void shift_env_vars(char ***env, int start)
{
    while ((*env)[start + 1]) {
        (*env)[start] = (*env)[start + 1];
        start++;
    }
    (*env)[start] = NULL;
}

int builtin_unsetenv(char **args, char ***env)
{
    int len;
    int i = 0;

    if (!args[1]) {
        write(2, "unsetenv: Too few arguments.\n", 28);
        return 1;
    }
    len = my_strlen(args[1]);
    while ((*env)[i]) {
        if (my_strncmp((*env)[i], args[1], len) == 0
            && (*env)[i][len] == '=') {
            free((*env)[i]);
            shift_env_vars(env, i);
            return 0;
        }
        i++;
    }
    return 0;
}

int builtin_exit(char **args, char ***env)
{
    int exit_code = 0;
    int i = 0;

    if (args[1])
        exit_code = my_atoi(args[1]);
    while ((*env)[i]) {
        free((*env)[i]);
        i++;
    }
    free(*env);
    exit(exit_code);
    return exit_code;
}
