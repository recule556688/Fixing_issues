##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for libmy
##

SRC	=	my_strcmp.c	\
		my_strdup.c	\
		my_atoi.c	\
		my_putchar.c	\
		my_putstr.c	\
		my_putfloat.c	\
		my_putnbr.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

CFLAGS	=	-Wall -Wextra -I../../include

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../
	mkdir -p ../../include
	cp ../../include/my.h ../../include/ || true

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re:	fclean all

.PHONY: all clean fclean re
