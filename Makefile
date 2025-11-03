CC = gcc -g -Wall -Wextra -Werror
MLXFALGS = -lXext -lX11 -lm

ARC = src/.mlx/libmlx_Linux.a
INC = inc/
MLXINC = src/.mlx/
HED = inc/cub3d.h
MLXHED = .mlx/mlx.h
#SRC = src/main.c utils/strutils0.c src/parser/parse_map_file.c
#SRC = $(shell find . -name "*.c")
SRC = $(shell find . -name "*.c" -not -path "./src/.mlx/*")
OBJ = $(SRC:.c=.o)

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -I$(INC) -I$(MLXINC) $(OBJ) $(ARC) $(MLXFALGS) -o $(NAME)
#$(NAME): $(OBJ)
#	$(CC) -I$(INC) -I$(MLXINC) $(ARC) $(OBJ) $(MLXFALGS) -o $(NAME)

%.o: %.c $(HED)
	$(CC) -I$(INC) -I$(MLXINC) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
