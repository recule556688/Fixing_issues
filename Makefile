##
## EPITECH PROJECT, 2025
## B-PSU-200-LYN-2-1-minishell1-luca.grange
## File description:
## Makefile
##

NAME = mysh

SRC = src/minishell.c \
      src/builtins.c \
      src/env.c \
      src/exec.c \
      src/string_utils.c \
      src/string_compare.c \
      src/parser.c \
      src/exec_pipeline.c \
      src/parser_utils.c \
      src/parser_utils_more.c \
      src/pipeline_utils.c \
      src/execute_utils.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I./includes
LDFLAGS =

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
