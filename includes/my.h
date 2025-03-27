/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-luca.grange
** File description:
** Main header file with all declarations
*/

#ifndef MY_H_
    #define MY_H_

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
    #include <stdbool.h>

    #define MAX_TOKENS 128
    #define MALLOC_ERR_MSG "Error: malloc failed\n"
    #define COMMAND_NOT_FOUND_MSG ": Command not found.\n"
    #define CD_NO_HOME_MSG "cd: No HOME variable set.\n"
    #define ENV_TOO_MANY_ARGS_MSG "env: Too many arguments.\n"
    #define SET_TOO_MANY_ARGS_MSG "setenv: Too many arguments.\n"
    #define UNSET_TOO_MANY_ARGS_MSG "unsetenv: Too many arguments.\n"
/* String structure */
typedef struct string_s {
    char *str;
    size_t len;
} string_t;

/* Command structures for parsing */
typedef struct command_s {
    char **args;           // Command arguments
    char *input_file;      // Input redirection file
    char *output_file;     // Output redirection file
    bool append_output;    // Flag for append mode (>>)
    struct command_s *next; // Next command in pipeline
} command_t;

typedef struct command_list_s {
    command_t *first;             // First command in this command list
    struct command_list_s *next;  // Next command list (after semicolon)
} command_list_t;

/* Shell structure */
typedef struct shell_s {
    char **env;
    int last_exit_status;
} shell_t;

/* Builtin command structure */
typedef struct builtin_cmd_s {
    const char *name;
    int (*func)(char **args, char ***env);
} builtin_cmd_t;

/* Global variables */
extern const builtin_cmd_t BUILTINS[];

/* String manipulation functions */
size_t my_strlen(const char *str);
char *my_strdup(const char *str);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, int n);
char *my_strchr(const char *s, int c);
int my_atoi(const char *s);

/* Environment functions */
char **copy_env(char **envp);
char *build_var_value(const char *var, const char *value);
char *get_env_value(char **env, const char *var);

/* Builtin commands */
int builtin_cd(char **args, char ***env);
int builtin_env(char **args, char ***env);
int builtin_setenv(char **args, char ***env);
int builtin_unsetenv(char **args, char ***env);
int builtin_exit(char **args, char ***env);

/* Parsing functions */
command_list_t *parse_input(char *input);
void free_command_list(command_list_t *list);

/* Command execution */
int execute_external(char **args, char **env);
int try_path_search(char **args, char *path_env);
int execute_command_list(command_list_t *cmd_list, shell_t *shell);
int execute_pipeline(command_t *pipeline, shell_t *shell);
int execute_command(command_t *cmd, shell_t *shell, int input_fd,
    int output_fd);

#endif /* !MY_H_ */
