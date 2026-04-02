##
## EPITECH PROJECT, 2025
## B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Iinclude
LIB = lib/libmy.a
SRC_DIR = src
LIB_DIR = lib/my
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)
TARGET = corewar

all: $(LIB) $(TARGET)

$(LIB):
	@$(MAKE) -C $(LIB_DIR)
	@echo "Library compiled and copied to lib/"

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

tests_run: all
	@echo "Running tests..."
	@./$(TARGET)

clean:
	@rm -f $(OBJ)
	@echo "Object files removed"

fclean: clean
	@rm -f $(TARGET)
	@rm -f $(LIB)
	@rm -f $(LIB_DIR)/libmy.a
	@echo "Executable and libraries removed"

re: fclean all

.PHONY: all tests_run clean fclean re
