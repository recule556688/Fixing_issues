/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell1-luca.grange
** File description:
** Command execution
*/

#ifndef EXEC_H_
    #define EXEC_H_

int execute_external(char **args, char **env);
int try_path_search(char **args, char *path_env);

#endif /* !EXEC_H_ */
