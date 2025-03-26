/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell1-luca.grange
** File description:
** Command execution functions
*/

#include "../includes/my.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int try_execute(const char *path, char **args, char **env)
{
    if (access(path, X_OK) == 0) {
        execve(path, args, env);
        return 0;
    }
    return -1;
}

static char *build_path(const char *dir, const char *cmd)
{
    int dir_len = my_strlen(dir);
    int cmd_len = my_strlen(cmd);
    char *path = malloc(dir_len + cmd_len + 2);

    if (!path) {
        write(2, "Error: malloc failed\n", 23);
        exit(84);
    }
    for (int i = 0; i < dir_len; i++)
        path[i] = dir[i];
    path[dir_len] = '/';
    for (int i = 0; i < cmd_len; i++)
        path[dir_len + 1 + i] = cmd[i];
    path[dir_len + cmd_len + 1] = '\0';
    return path;
}

int try_path_search(char **args, char *path_env)
{
    char *path_dup = my_strdup(path_env);
    char *token;
    char *saveptr;
    char *candidate;
    int result = -1;

    token = strtok_r(path_dup, ":", &saveptr);
    while (token && result == -1) {
        candidate = build_path(token, args[0]);
        if (try_execute(candidate, args, NULL) == 0)
            result = 0;
        free(candidate);
        token = strtok_r(NULL, ":", &saveptr);
    }
    free(path_dup);
    return result;
}

static char *find_path_env(char **env)
{
    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], "PATH=", 5) == 0)
            return env[i] + 5;
    }
    return NULL;
}

int execute_external(char **args, char **env)
{
    char *path_env;

    if (my_strchr(args[0], '/')) {
        if (try_execute(args[0], args, env) == 0)
            return 0;
    } else {
        path_env = find_path_env(env);
        if (path_env && try_path_search(args, path_env) == 0)
            return 0;
    }
    write(2, args[0], my_strlen(args[0]));
    write(2, ": Command not found.\n", 21);
    exit(1);
}
