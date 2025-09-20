CC = gcc -g #-Wall -Wextra -Werror

INC = inc/
HED = inc/cub3d.h
#SRC = src/main.c utils/strutils0.c src/parser/parse_map_file.c
SRC = $(shell find . -name "*.c")
OBJ = $(SRC:.c=.o)

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -I$(INC) $(OBJ) -o $(NAME)

%.o: %.c $(HED)
	$(CC) -I$(INC) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean