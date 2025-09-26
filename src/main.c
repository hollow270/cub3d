/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:28:41 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/26 20:14:44 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_extension(char *file_name);

/*#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

static void	init_player(t_game *g, char **map)
{
	int y = 0;
	while (map[y])
	{
		int x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				g->player.pos_x = x + 0.5;
				g->player.pos_y = y + 0.5;
				if (map[y][x] == 'N')
				{
					g->player.dir_x = 0; g->player.dir_y = -1;
					g->player.plane_x = 0.66; g->player.plane_y = 0;
				}
				else if (map[y][x] == 'S')
				{
					g->player.dir_x = 0; g->player.dir_y = 1;
					g->player.plane_x = -0.66; g->player.plane_y = 0;
				}
				else if (map[y][x] == 'E')
				{
					g->player.dir_x = 1; g->player.dir_y = 0;
					g->player.plane_x = 0; g->player.plane_y = 0.66;
				}
				else if (map[y][x] == 'W')
				{
					g->player.dir_x = -1; g->player.dir_y = 0;
					g->player.plane_x = 0; g->player.plane_y = -0.66;
				}
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	put_pixel(t_img *img, int x, int y, int color)
{
	if (x >= 0 && x < 800 && y >= 0 && y < 600)
		img->data[y * (img->line_len / 4) + x] = color;
}

static void	render_frame(t_game *g)
{
	int x;

	for (x = 0; x < g->win_w; x++)
	{
		double cameraX = 2 * x / (double)g->win_w - 1;
		double rayDirX = g->player.dir_x + g->player.plane_x * cameraX;
		double rayDirY = g->player.dir_y + g->player.plane_y * cameraX;

		int mapX = (int)g->player.pos_x;
		int mapY = (int)g->player.pos_y;

		double sideDistX, sideDistY;
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;
		int stepX, stepY, hit = 0, side;

		if (rayDirX < 0) { stepX = -1; sideDistX = (g->player.pos_x - mapX) * deltaDistX; }
		else { stepX = 1; sideDistX = (mapX + 1.0 - g->player.pos_x) * deltaDistX; }
		if (rayDirY < 0) { stepY = -1; sideDistY = (g->player.pos_y - mapY) * deltaDistY; }
		else { stepY = 1; sideDistY = (mapY + 1.0 - g->player.pos_y) * deltaDistY; }

		while (hit == 0)
		{
			if (sideDistX < sideDistY) { sideDistX += deltaDistX; mapX += stepX; side = 0; }
			else { sideDistY += deltaDistY; mapY += stepY; side = 1; }
			if (g->vars->p_data.matrix[mapY][mapX] == '1') hit = 1;
		}

		if (side == 0) perpWallDist = (mapX - g->player.pos_x + (1 - stepX) / 2) / rayDirX;
		else perpWallDist = (mapY - g->player.pos_y + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(g->win_h / perpWallDist);
		int drawStart = -lineHeight / 2 + g->win_h / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + g->win_h / 2;
		if (drawEnd >= g->win_h) drawEnd = g->win_h - 1;

		int color = (side == 0) ? 0xFF0000 : 0x880000;
		for (int y = drawStart; y < drawEnd; y++)
			put_pixel(&g->img, x, y, color);
	}
}

static int	handle_key(int keycode, t_game *g)
{
	if (keycode == 65307) // ESC
	{
		mlx_destroy_window(g->vars->mlx, g->vars->win);
		exit(0);
	}
	else if (keycode == 'w') // forward
	{
		int nx = (int)(g->player.pos_x + g->player.dir_x * MOVE_SPEED);
		int ny = (int)(g->player.pos_y + g->player.dir_y * MOVE_SPEED);
		if (g->vars->p_data.matrix[(int)g->player.pos_y][nx] != '1')
			g->player.pos_x += g->player.dir_x * MOVE_SPEED;
		if (g->vars->p_data.matrix[ny][(int)g->player.pos_x] != '1')
			g->player.pos_y += g->player.dir_y * MOVE_SPEED;
	}
	else if (keycode == 's') // backward
	{
		int nx = (int)(g->player.pos_x - g->player.dir_x * MOVE_SPEED);
		int ny = (int)(g->player.pos_y - g->player.dir_y * MOVE_SPEED);
		if (g->vars->p_data.matrix[(int)g->player.pos_y][nx] != '1')
			g->player.pos_x -= g->player.dir_x * MOVE_SPEED;
		if (g->vars->p_data.matrix[ny][(int)g->player.pos_x] != '1')
			g->player.pos_y -= g->player.dir_y * MOVE_SPEED;
	}
	else if (keycode == 'a') // strafe left
	{
		double strafe_x = g->player.dir_y;  // Fixed: was -g->player.dir_y
		double strafe_y = -g->player.dir_x; // Fixed: was g->player.dir_x
		int nx = (int)(g->player.pos_x + strafe_x * MOVE_SPEED);
		int ny = (int)(g->player.pos_y + strafe_y * MOVE_SPEED);
		if (g->vars->p_data.matrix[(int)g->player.pos_y][nx] != '1')
			g->player.pos_x += strafe_x * MOVE_SPEED;
		if (g->vars->p_data.matrix[ny][(int)g->player.pos_x] != '1')
			g->player.pos_y += strafe_y * MOVE_SPEED;
	}
	else if (keycode == 'd') // strafe right
	{
		double strafe_x = -g->player.dir_y; // Fixed: was g->player.dir_y
		double strafe_y = g->player.dir_x;  // Fixed: was -g->player.dir_x
		int nx = (int)(g->player.pos_x + strafe_x * MOVE_SPEED);
		int ny = (int)(g->player.pos_y + strafe_y * MOVE_SPEED);
		if (g->vars->p_data.matrix[(int)g->player.pos_y][nx] != '1')
			g->player.pos_x += strafe_x * MOVE_SPEED;
		if (g->vars->p_data.matrix[ny][(int)g->player.pos_x] != '1')
			g->player.pos_y += strafe_y * MOVE_SPEED;
	}
	else if (keycode == 65361 || keycode == 123) // left arrow
	{
		double oldDirX = g->player.dir_x;
		g->player.dir_x = g->player.dir_x * cos(-ROT_SPEED) - g->player.dir_y * sin(-ROT_SPEED); // Fixed: negated ROT_SPEED
		g->player.dir_y = oldDirX * sin(-ROT_SPEED) + g->player.dir_y * cos(-ROT_SPEED);        // Fixed: negated ROT_SPEED
		double oldPlaneX = g->player.plane_x;
		g->player.plane_x = g->player.plane_x * cos(-ROT_SPEED) - g->player.plane_y * sin(-ROT_SPEED); // Fixed: negated ROT_SPEED
		g->player.plane_y = oldPlaneX * sin(-ROT_SPEED) + g->player.plane_y * cos(-ROT_SPEED);         // Fixed: negated ROT_SPEED
	}
	else if (keycode == 65363 || keycode == 124) // right arrow
	{
		double oldDirX = g->player.dir_x;
		g->player.dir_x = g->player.dir_x * cos(ROT_SPEED) - g->player.dir_y * sin(ROT_SPEED); // Fixed: removed negation
		g->player.dir_y = oldDirX * sin(ROT_SPEED) + g->player.dir_y * cos(ROT_SPEED);        // Fixed: removed negation
		double oldPlaneX = g->player.plane_x;
		g->player.plane_x = g->player.plane_x * cos(ROT_SPEED) - g->player.plane_y * sin(ROT_SPEED); // Fixed: removed negation
		g->player.plane_y = oldPlaneX * sin(ROT_SPEED) + g->player.plane_y * cos(ROT_SPEED);         // Fixed: removed negation
	}
	return (0);
}

static int	handle_close(t_game *g)
{
	mlx_destroy_window(g->vars->mlx, g->vars->win);
	exit(0);
	return (0);
}

static int	loop_hook(t_game *g)
{
	for (int i = 0; i < g->win_w * (g->win_h / 2); i++)
		g->img.data[i] = 0x87CEEB; // sky color
	for (int i = g->win_w * (g->win_h / 2); i < g->win_w * g->win_h; i++)
		g->img.data[i] = 0x8B4513; // sky color

	render_frame(g);
	mlx_put_image_to_window(g->vars->mlx, g->vars->win, g->img.img, 0, 0);
	return (0);
}

void	init_game(t_vars *vars)
{
	t_game *g = gc_malloc(sizeof(t_game));

	g->vars = vars;
	g->win_w = 800;
	g->win_h = 600;

	init_player(g, vars->p_data.matrix);

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, g->win_w, g->win_h, "Cub3D");
	g->img.img = mlx_new_image(vars->mlx, g->win_w, g->win_h);
	g->img.data = (int *)mlx_get_data_addr(g->img.img,
			&g->img.bpp, &g->img.line_len, &g->img.endian);

	mlx_loop_hook(vars->mlx, loop_hook, g);
	mlx_hook(vars->win, 2, 1L<<0, handle_key, g);   // key press
	mlx_hook(vars->win, 17, 0, handle_close, g);    // close window

	mlx_loop(vars->mlx);
}*/

#define PI 3.14159
#define CUBE_SIZE 64
#define RAY_WIDTH 3
#define PLAYER_SIZE 10
#define ROT_SPEED 3
#define MOVE_SPEED 0.1
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define PLAYER_COLOR 0xFF0000

/*int	check_new_position(double new_x, double new_y, t_game *g, int dir)
{
	float	cast_y;
	float	cast_x;

	cast_y = new_y;
	cast_x = new_x;
	if (dir == 'a' || dir == 'w')
	{
		if (g->vars->p_data.matrix[(int)(new_y)][(int)(new_x)] == '1')
			return (0);
	}
	else if (dir == 'd' || dir == 's')
	{
		if (g->vars->p_data.matrix[(int)(new_y + 0.1)][(int)(new_x + 0.1)] == '1')
			return (0);
	}
	return (1);
}*/

int check_new_position(double new_x, double new_y, t_game *g, int dir)
{
    double player_size_in_map = (double)PLAYER_SIZE / CUBE_SIZE;
    
    if (dir == 'a' || dir == 'w')
    {
        // For left/up movement, check top-left corner
        if (g->vars->p_data.matrix[(int)(new_y)][(int)(new_x)] == '1')
            return (0);
    }
    else if (dir == 'd')
    {
        // For right movement, check top-right corner
        if (g->vars->p_data.matrix[(int)(new_y)][(int)(new_x + player_size_in_map)] == '1')
            return (0);
    }
    else if (dir == 's')
    {
        // For down movement, check bottom-left corner
        if (g->vars->p_data.matrix[(int)(new_y + player_size_in_map)][(int)(new_x)] == '1')
            return (0);
    }
    return (1);
}

int	controls(int keycode, t_game *g)
{
	if (keycode == 'w' && check_new_position(g->player.pos_x, g->player.pos_y - MOVE_SPEED, g, 'w'))
		g->player.pos_y -= MOVE_SPEED;
	else if (keycode == 'd' && check_new_position(g->player.pos_x + MOVE_SPEED, g->player.pos_y, g, 'd'))
		g->player.pos_x += MOVE_SPEED;
	else if (keycode == 's' && check_new_position(g->player.pos_x, g->player.pos_y + MOVE_SPEED, g, 's'))
		g->player.pos_y += MOVE_SPEED;
	else if (keycode == 'a' && check_new_position(g->player.pos_x - MOVE_SPEED, g->player.pos_y, g, 'a'))
		g->player.pos_x -= MOVE_SPEED;
	else if (keycode == 65361 || keycode == 123) // left arrow
		g->player.angle -= ROT_SPEED;
	else if (keycode == 65363 || keycode == 124) // right arrow
		g->player.angle += ROT_SPEED;
}

void	render_ray_points(int x, int y, t_game *g)
{
	int		start_x;
	int		start_y;

	int		player_x;
	int		player_y;

	int		pixel_x;
	int		pixel_y;

	start_x = x;
	start_y = y;
	player_y = 0;
	while (player_y < RAY_WIDTH)
	{
		player_x = 0;
		while (player_x < RAY_WIDTH)
		{
			pixel_x = start_x + player_x - RAY_WIDTH / 2;
			pixel_y = start_y + player_y - RAY_WIDTH / 2;
			int	index = pixel_y * (g->img.line_len / 4) + pixel_x;
			g->img.data[index] = PLAYER_COLOR;
			player_x++;
		}
		player_y++;
	}
}

void	render_vision_ray(t_game *g)
{
	double	angle = g->player.angle * PI / 180;
	int p_x = (int)(g->player.pos_x * CUBE_SIZE);
	int	p_y = (int)(g->player.pos_y * CUBE_SIZE);
	int	end_x = p_x + cos(angle) * 100;
	int	end_y = p_y + sin(angle) * 100;
	int	d_x = end_x - p_x;
	int	d_y = end_y - p_y;
	int	steps;

	if (abs(d_x) > abs(d_y))
		steps = abs(d_x);
	else
		steps = abs(d_y);

	double	m = (double)d_y / d_x;
	int i = 0;
	while (i <= steps)
	{
		int	x = p_x + (i * d_x) / steps;
		int	y = p_y + (i * d_y) / steps;
		render_ray_points(x, y, g);
		//mlx_pixel_put(g->vars->mlx, g->vars->win, p_x + i, p_y + i * m, PLAYER_COLOR);
		i++;
	}
}

void	render_player(t_game *g)
{
	int		start_player_x;
	int		start_player_y;

	int		player_x;
	int		player_y;

	int		pixel_x;
	int		pixel_y;

	char	**map = g->vars->p_data.matrix;

	start_player_x = g->player.pos_x * CUBE_SIZE;
	start_player_y = g->player.pos_y * CUBE_SIZE;
	player_y = 0;
	while (player_y < PLAYER_SIZE)
	{
		player_x = 0;
		while (player_x < PLAYER_SIZE)
		{
			pixel_x = start_player_x + player_x - PLAYER_SIZE / 2;
			pixel_y = start_player_y + player_y - PLAYER_SIZE / 2;
			int	index = pixel_y * (g->img.line_len / 4) + pixel_x;
			g->img.data[index] = PLAYER_COLOR;
			player_x++;
		}
		player_y++;
	}
}

void	render_map(t_game *g)
{
	// char **map line coordinates
	int	map_x;
	int	map_y;
	// mlx window pixels coordinates
	int	pixel_x;
	int	pixel_y;
	// coordinates of the cube currently being drawn in the two last while loops
	int	cube_x;
	int	cube_y;
	// coordinates of the first pixel in the cube to draw in each loop
	int	start_cube_x;
	int	start_cube_y;
	// index needed to know where to change the pixels in the mlx img int *data array
	int	index;
	// parsed char **map from the parsing part
	char	**map;

	map_y = 0;
	map = g->vars->p_data.matrix;
	// looping through the char **map first
	while (map[map_y])
	{
		map_x = 0;
		while (map[map_y][map_x])
		{
			// check if the current char in char **map is '1'
			if (map[map_y][map_x] == '1')
			{
				// calculate the position from which we should start drawing the cube
				start_cube_x = map_x * CUBE_SIZE; 
				start_cube_y = map_y * CUBE_SIZE;
				// loop through the cube coordinates
				cube_y = 0;
				while (cube_y < CUBE_SIZE)
				{
					cube_x = 0;
					while (cube_x < CUBE_SIZE)
					{
						// calculate the current cube coordinates reached
						pixel_x = start_cube_x + cube_x;
						pixel_y = start_cube_y + cube_y;
						// convert 2d coordinates to 1d coordinate
						index = pixel_y * (g->img.line_len / 4) + pixel_x;
						g->img.data[index] = WHITE;
						cube_x++;
					}
					cube_y++;
				}
			}
			map_x++;
		}
		map_y++;
	}
}

int	render(t_game *g)
{
	int	i;

	i = 0;
	while (i <= g->win_h * g->win_w)
	{
		g->img.data[i++] = BLACK;
	}
	render_map(g);
	render_player(g);
	render_vision_ray(g);
	//printf("player = [%f, %f]\n", g->player.pos_x, g->player.pos_y);
	mlx_put_image_to_window(g->vars->mlx, g->vars->win, g->img.img, 0, 0);
}

void	cube_init(t_vars *vars)
{
	t_game	*g = gc_malloc(sizeof(t_game));

	g->vars = vars;
	g->win_w = 800;
	g->win_h = 600;
	g->player.pos_x = (double) g->vars->p_data.p_x;
	g->player.pos_y = (double) g->vars->p_data.p_y;
	g->player.angle = 0;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 800, 600, "Dungeon gayme");
	g->img.img = mlx_new_image(g->vars->mlx, g->win_w, g->win_h);
	g->img.data = (int *)mlx_get_data_addr(g->img.img, &g->img.bpp, &g->img.line_len, &g->img.endian);
	mlx_loop_hook(g->vars->mlx, render, g);
	mlx_hook(vars->win, 2, 1L<<0, controls, g);
	mlx_loop(vars->mlx);
	render(g);
}

int	main(int argc, char *argv[])
{
	//t_parse_data	data;
	t_vars			vars;

	if (argc != 2)
		return (printf("Error\nInvalid arguments\n"), 1);
	if (check_extension(argv[1]) == 0)
		return (printf("Error\nInvalid file extension\n"), 2);
	if (parse_map_file(argv[1], &vars.p_data) == 0 || vars.p_data.is_valid == 0)
		return (gc_free_all(), 3);
	printf("p_x = [%f]\np_y = [%f]\n", vars.p_data.p_x, vars.p_data.p_y);
	char	**map = vars.p_data.matrix;
	int		i = 0;

	while (map[i])
		printf("[%s]\n", map[i++]);
	//init_game(&vars);
	cube_init(&vars);
	gc_free_all();
	return (0);
}

int	check_extension(char *file_name)
{
	int	i;

	i = 0;
	if (file_name[i] == '.' && ft_strcmp(file_name, ".cub"))
		return (0);
	while (file_name[i] && file_name[i] != '.')
		i++;
	if (!file_name[i])
		return (0);
	if (ft_strcmp(file_name + i, ".cub") != 0)
		return (0);
	return (1);
}