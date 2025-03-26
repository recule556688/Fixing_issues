/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell1-luca.grange
** File description:
** Environment handling functions
*/

#include "../includes/my.h"
#include <stdlib.h>
#include <unistd.h>

static char **allocate_env_copy(int count)
{
    char **env_copy = malloc(sizeof(char *) * (count + 1));

    if (!env_copy) {
        write(2, "Error: malloc failed\n", 23);
        exit(84);
    }
    return env_copy;
}

char **copy_env(char **envp)
{
    int count = 0;
    char **env_copy;

    while (envp[count])
        count++;
    env_copy = allocate_env_copy(count);
    for (int i = 0; i < count; i++)
        env_copy[i] = my_strdup(envp[i]);
    env_copy[count] = NULL;
    return env_copy;
}

static char *allocate_var_str(int len_var, int len_val)
{
    char *str = malloc(len_var + len_val + 2);

    if (!str) {
        write(2, "Error: malloc failed\n", 23);
        exit(84);
    }
    return str;
}

static void fill_var_str(char *str, const char *var, const char *value)
{
    int i = 0;

    while (*var) {
        str[i] = *var;
        i++;
        var++;
    }
    str[i] = '=';
    i++;
    while (*value) {
        str[i] = *value;
        i++;
        value++;
    }
    str[i] = '\0';
}

char *build_var_value(const char *var, const char *value)
{
    int len_var = my_strlen(var);
    int len_val = my_strlen(value);
    char *str = allocate_var_str(len_var, len_val);

    fill_var_str(str, var, value);
    return str;
}

char *get_env_value(char **env, const char *var)
{
    int len = my_strlen(var);

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
            return env[i] + len + 1;
    }
    return NULL;
}
