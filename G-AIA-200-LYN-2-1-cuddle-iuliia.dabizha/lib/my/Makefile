##
## EPITECH PROJECT, 2024
## libmy
## File description:
## Makefile to compile the libmy library and manage temporary files
##

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
NAME = libcuddle.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../

clean:
	@rm -f $(OBJ)
	@echo "Object files removed"

fclean: clean
	@rm -f ../$(NAME)
	@rm -f $(NAME)
	@echo "Library removed from lib/"

re: fclean all

.PHONY: all clean fclean re
