/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:28:41 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/23 14:35:10 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_extension(char *file_name);

#define MOVE_SPEED 0.1
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
	init_game(&vars);
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