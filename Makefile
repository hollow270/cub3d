CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O3

MLX_DIR = .mlx/
MLX = .mlx/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# SRC = cub3d.c parser.c rendering.c hooks.c move_player.c minimap.c inside_portal.c
SRC = $(shell find . -name "*.c" -not -path "./.mlx/*")
OBJ = $(SRC:.c=.o)

NAME = cub3d

all : $(MLX) $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR) CC=$(CC)

$(NAME): $(OBJ) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $@

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -I. -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean || true

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : clean
