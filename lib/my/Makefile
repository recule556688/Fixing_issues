##
## EPITECH PROJECT, 2024
## B-CPE-110-LYN-1-1-organized-iuliia.dabizha
## File description:
## Makefile
##

SRC =   handle_char.c \
		handle_float.c \
		handle_int.c \
		handle_pointer.c \
		handle_string.c \
		handle_unsigned_int.c \
		handle_unsigned_int_hexa.c \
		handle_unsigned_int_octal.c \
		my_printf.c \
		my_putchar.c \
		my_put_nbr.c \
		my_putstr.c \
		my_strlen.c \
		my_put_unsigned_nbr_base.c \
		my_put_unsigned_nbr.c \
		utilities_functions.c \
		my_put_pointer_nbr_base.c \
		print_specials.c \
		my_putfloat.c \
		padding.c \
		parse_format.c \
		printf_numeric.c \
		printf_hex.c \
		printf_char.c \
		my_strdup.c \
		my_strcpy.c \
		my_strcmp.c \
		my_getnbr.c \
		my_memcpy.c \
		my_atoi.c \

OBJ = $(SRC:.c=.o)
NAME = libmy.a
INCLUDE = ../../include

all: $(NAME) clean

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../
	mkdir -p $(INCLUDE)
	cp my.h $(INCLUDE)
	cp struct.h $(INCLUDE)
	@echo "Library compiled and copied to lib/"
	make clean
	@echo "Object files removed"

clean:
	@rm -f $(OBJ)
	@echo "Object files removed"

fclean: clean
	@rm -f ../$(NAME)
	@rm -f $(NAME)
	@echo "Library removed from lib/"

re: fclean all

.PHONY: all clean fclean re
