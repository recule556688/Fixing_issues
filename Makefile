##
## EPITECH PROJECT, 2025
## B-PSU-200-LYN-2-1-minishell1-luca.grange
## File description:
## Makefile
##

NAME = mysh

SRC = src/minishell.c \
      src/string_utils.c \
      src/string_compare.c \
      src/builtins.c \
      src/env.c \
      src/exec.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I./includes
LDFLAGS =

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
	cp $(NAME) tester

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) tester/$(NAME)

re: fclean all

.PHONY: all clean fclean re
