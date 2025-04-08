##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Main Makefile
##

NAME	=	maze

SRC	=	src/main.c		\
		src/parsing.c		\
		src/room_operations.c	\
		src/print.c		\
		src/memory.c		\
		src/utils.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -I./include

LDFLAGS	=	-L./lib -lmy

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