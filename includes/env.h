/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell1-luca.grange
** File description:
** Environment handling
*/

#ifndef ENV_H_
    #define ENV_H_

char **copy_env(char **envp);
char *build_var_value(const char *var, const char *value);
char *get_env_value(char **env, const char *var);

#endif /* !ENV_H_ */
