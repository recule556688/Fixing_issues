##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Main Makefile
##

NAME	=	maze

SRC	=	src/main.c		\
		src/parsing/parsing.c		\
		src/parsing/room_operations.c	\
		src/parsing/print.c		\
		src/parsing/memory.c		\
		src/parsing/utils.c		\
		src/parsing/utils_two.c		\
		src/algo/dijkstra.c		\
		src/algo/robot_paths.c		\
		src/algo/path_operations.c	\
		src/algo/node_operations.c	\
		src/algo/path_operations_utilies.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -I./include -g -fsanitize=address

LDFLAGS	=	-L./lib -lmy -fsanitize=address

all:	$(NAME)

$(NAME):	make_lib $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

make_lib:
	mkdir -p include
	cp lib/my/my.h include/
	make -C lib/my

clean:
	make -C lib/my clean
	rm -f $(OBJ)

fclean:	clean
	make -C lib/my fclean
	rm -f $(NAME)
	rm -f include/my.h

re:	fclean all

.PHONY: all make_lib clean fclean re
