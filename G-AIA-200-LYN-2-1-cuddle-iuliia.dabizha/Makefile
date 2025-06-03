##
## EPITECH PROJECT, 2024
## B-CPE-110-LYN-1-1-settingup-iuliia.dabizha
## File description:
## Makefile
##

SRC = src/main.c \
		src/test_dataframe_io.c \
		src/test_dataframe_operations.c \

OBJ = $(SRC:.c=.o)
NAME = cuddle
LIB_DIR = ./lib/my
INCLUDE_DIR = ./include
LIBMY = $(LIB_DIR)/libcuddle.a

all: $(NAME)

$(NAME): $(SRC) $(OBJ) $(LIBMY)
	gcc -o $(NAME) $(OBJ) -L$(LIB_DIR) -lcuddle -I$(INCLUDE_DIR)
	@echo "$(NAME) compiled with libmy"
	make clean
	@echo "Object files removed"

$(LIBMY):
	make -C $(LIB_DIR)
	cp $(LIBMY) .
	@echo "Libmy.a was copied to the root folder"

clean:
	@rm -f $(OBJ)
	make -C $(LIB_DIR) clean
	@echo "Object files removed"

fclean: clean
	@rm -f $(NAME)
	@rm -f libcuddle.a
	make -C $(LIB_DIR) fclean
	@echo "Executable $(NAME) removed"

re: fclean all

.PHONY: all clean fclean re
