/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:28:41 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/27 17:32:44 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_extension(char *file_name);

#define PI 3.14159
#define	FOV 60
#define CUBE_SIZE 64
#define MINIMAP_SIZE 10
#define RAY_WIDTH 3
#define PLAYER_SIZE 10
#define ROT_SPEED 10
#define MOVE_SPEED 0.3
#define WHITE 0xFFFFFF
#define GROUND 0x2b2b2a
#define SKY 0x87CEEB
#define BLACK 0x000000
#define PLAYER_COLOR 0xFF0000
#define PX_SIZE 2

int check_new_position(double new_x, double new_y, t_game *g, int dir)
{
    double player_size_in_map = (double)PLAYER_SIZE / CUBE_SIZE;
    
    if (dir == 'a' || dir == 'w')
    {
        if (g->vars->p_data.matrix[(int)(new_y)][(int)(new_x)] == '1')
            return (0);
    }
    else if (dir == 'd')
    {
        if (g->vars->p_data.matrix[(int)(new_y)][(int)(new_x + player_size_in_map)] == '1')
            return (0);
    }
    else if (dir == 's')
    {
        if (g->vars->p_data.matrix[(int)(new_y + player_size_in_map)][(int)(new_x)] == '1')
            return (0);
    }
    return (1);
}

int	controls(int keycode, t_game *g)
{
	double	angle = g->player.angle * PI / 180;
	if (keycode == 'w')
	{
		double new_x = g->player.pos_x + cos(angle) * MOVE_SPEED;
		double new_y = g->player.pos_y + sin(angle) * MOVE_SPEED;
		if (check_new_position(new_x, new_y, g, 'w'))
		{
			g->player.pos_x = new_x;
			g->player.pos_y = new_y;
		}
	}
		//g->player.pos_y -= MOVE_SPEED;
	else if (keycode == 'd' && check_new_position(g->player.pos_x + MOVE_SPEED, g->player.pos_y, g, 'd'))
		g->player.pos_x += MOVE_SPEED;
	else if (keycode == 's')
	{
		double new_x = g->player.pos_x + cos(angle) * (-MOVE_SPEED);
		double new_y = g->player.pos_y + sin(angle) * (-MOVE_SPEED);
		if (check_new_position(new_x, new_y, g, 's'))
		{
			g->player.pos_x = new_x;
			g->player.pos_y = new_y;
		}
	}
		//g->player.pos_y += MOVE_SPEED;
	else if (keycode == 'a' && check_new_position(g->player.pos_x - MOVE_SPEED, g->player.pos_y, g, 'a'))
		g->player.pos_x -= MOVE_SPEED;
	/*else if (keycode == 65361 || keycode == 123) // left arrow
		g->player.angle -= ROT_SPEED;
	else if (keycode == 65363 || keycode == 124) // right arrow
		g->player.angle += ROT_SPEED;*/
	if (keycode == 65361 || keycode == 123)
	{
		g->player.angle -= ROT_SPEED;
		if (g->player.angle < 0)
			g->player.angle += 360;
	}
	else if (keycode == 65363 || keycode == 124)
	{
		g->player.angle += ROT_SPEED;
		if (g->player.angle >= 360)
			g->player.angle -= 360;
	}
}

void	render_ray_points(int x, int y, t_game *g, int color)
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
			mlx_pixel_put(g->vars->mlx, g->vars->win, pixel_x, pixel_y, color);
			//int	index = pixel_y * (g->img.line_len / 4) + pixel_x;
			//g->img.data[index] = color;
			player_x++;
		}
		player_y++;
	}
}

int	is_wall(t_game *g, double x, double y)
{
	char	**map;
	int		map_x;
	int		map_y;
	int		width;
	int		height;

	map_x = (int)x / 64;
	map_y = (int)y / 64;
	width = g->vars->p_data.width;
	height = g->vars->p_data.height;
	if (map_x < 0 || map_x >= width || map_y < 0 || map_y >= height)
		return (1);
	map = g->vars->p_data.matrix;
	//if (map[(int)(y / 64)][(int)(x / 64)] == '1')
	if (map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	init_raycast_data(t_game *g)
{
	g->rcd = gc_malloc(sizeof(t_raycast));
	g->rcd->p_p = gc_malloc(sizeof(t_pos));
	g->rcd->p_p->x = g->player.pos_x * 64;
	g->rcd->p_p->y = g->player.pos_y * 64;
	g->rcd->angle = g->player.angle * PI / 180;
	//g->rcd->ray_angles = gc_malloc(sizeof(double) * g->win_w);
	g->rcd->h_p = gc_malloc(sizeof(t_pos));
	g->rcd->v_p = gc_malloc(sizeof(t_pos));
	g->rcd->tip_p = gc_malloc(sizeof(t_pos));
	g->rcd->tip_p->x = 0;
	g->rcd->tip_p->y = 0;
}

void	get_horizontal_intercept(t_game *g, double angle)
{
	double	x_step;
	double	y_step;
	int		max_i;

	if (fabs(sin(angle)) < 0.0001)
	{
		g->rcd->h_p->x = g->rcd->p_p->x;
		g->rcd->h_p->y = g->rcd->p_p->y;
		return;
	}

	// Ray pointing up (270° direction, angle > 180 in screen coords)
	if (angle > PI)
	{
		g->rcd->h_p->y = floor(g->rcd->p_p->y / 64) * 64;
		// If exactly on grid line, move one step back
		if (g->rcd->h_p->y == g->rcd->p_p->y)
			g->rcd->h_p->y -= 64;
		y_step = -64;
	}
	else  // Ray pointing down (90° direction)
	{
		g->rcd->h_p->y = ceil(g->rcd->p_p->y / 64) * 64;
		// If exactly on grid line, move one step forward
		if (g->rcd->h_p->y == g->rcd->p_p->y)
			g->rcd->h_p->y += 64;
		y_step = 64;
	}
	
	g->rcd->h_p->x = g->rcd->p_p->x + ((g->rcd->h_p->y - g->rcd->p_p->y) / tan(angle));
	x_step = y_step / tan(angle);
	
	max_i = 100;
	while (max_i != 0)
	{
		double check_y = g->rcd->h_p->y;
		if (y_step < 0)
			check_y -= 1;
		
		if (is_wall(g, g->rcd->h_p->x, check_y))
			break;
		
		g->rcd->h_p->x += x_step;
		g->rcd->h_p->y += y_step;
		max_i--;
	}
}

void	get_vertical_intercept(t_game *g, double angle)
{
	double	x_step;
	double	y_step;
	int		max_i;

	if (fabs(cos(angle)) < 0.0001)
	{
		g->rcd->v_p->x = g->rcd->p_p->x;
		g->rcd->v_p->y = g->rcd->p_p->y;
		return;
	}

	// Ray pointing right (0° direction)
	if (cos(angle) > 0)
	{
		g->rcd->v_p->x = ceil(g->rcd->p_p->x / 64) * 64;
		// If exactly on grid line, move one step forward
		if (g->rcd->v_p->x == g->rcd->p_p->x)
			g->rcd->v_p->x += 64;
		x_step = 64;
	}
	else  // Ray pointing left (180° direction)
	{
		g->rcd->v_p->x = floor(g->rcd->p_p->x / 64) * 64;
		// If exactly on grid line, move one step back
		if (g->rcd->v_p->x == g->rcd->p_p->x)
			g->rcd->v_p->x -= 64;
		x_step = -64;
	}
	
	g->rcd->v_p->y = g->rcd->p_p->y + ((g->rcd->v_p->x - g->rcd->p_p->x) * tan(angle));
	y_step = x_step * tan(angle);
	
	max_i = 100;
	while (max_i != 0)
	{
		double check_x = g->rcd->v_p->x;
		if (x_step < 0)
			check_x -= 1;
		
		if (is_wall(g, check_x, g->rcd->v_p->y))
			break;
		
		g->rcd->v_p->x += x_step;
		g->rcd->v_p->y += y_step;
		max_i--;
	}
}

void	choose_ray_tip(t_game *g)
{
	double	h_dist;
	double	v_dist;

	h_dist = sqrt(((g->rcd->h_p->x - g->rcd->p_p->x) * (g->rcd->h_p->x - g->rcd->p_p->x)) + 
	              ((g->rcd->h_p->y - g->rcd->p_p->y) * (g->rcd->h_p->y - g->rcd->p_p->y)));
	v_dist = sqrt(((g->rcd->v_p->x - g->rcd->p_p->x) * (g->rcd->v_p->x - g->rcd->p_p->x)) + 
	              ((g->rcd->v_p->y - g->rcd->p_p->y) * (g->rcd->v_p->y - g->rcd->p_p->y)));
	if (h_dist == 0)
	{
		g->rcd->tip_p->x = g->rcd->v_p->x;
		g->rcd->tip_p->y = g->rcd->v_p->y;
		g->rcd->wall_type = VERTICAL;
		return ;
	}
	else if (v_dist == 0)
	{
		g->rcd->tip_p->x = g->rcd->h_p->x;
		g->rcd->tip_p->y = g->rcd->h_p->y;
		g->rcd->wall_type = HORIZONTAL;
		return ;
	}
	else if (h_dist <= v_dist)
	{
		g->rcd->tip_p->x = g->rcd->h_p->x;
		g->rcd->tip_p->y = g->rcd->h_p->y;
		g->rcd->wall_type = HORIZONTAL;
	}
	else
	{
		g->rcd->tip_p->x = g->rcd->v_p->x;
		g->rcd->tip_p->y = g->rcd->v_p->y;
		g->rcd->wall_type = VERTICAL;
	}
}

void	render_point_debug(t_game *g, int x, int y, int color)
{
	int		start_player_x;
	int		start_player_y;

	int		player_x;
	int		player_y;

	int		pixel_x;
	int		pixel_y;

	start_player_x = x;
	start_player_y = y;
	if (x > g->win_w)
		start_player_x = g->win_w;
	else if (x < 0)
		start_player_x = 0;
	if (y > g->win_h)
		start_player_y = g->win_h;
	else if (y < 0)
		start_player_y = 0;
	player_y = 0;
	while (player_y < PLAYER_SIZE)
	{
		player_x = 0;
		while (player_x < PLAYER_SIZE)
		{
			pixel_x = start_player_x + player_x;
			pixel_y = start_player_y + player_y;
			int	index = pixel_y * (g->img.line_len / 4) + pixel_x;
			g->img.data[index] = color;
			player_x++;
		}
		player_y++;
	}
}

void	init_ray_angles(t_game *g, double *ray_angles)
{
	int		i;
	double	start_angle;

	i = 0;
	//start_angle = (((double)FOV / 2) * -1);
	start_angle = g->player.angle + (((double)FOV / 2) * -1);
	//printf("start_angle = [%f]\nplayer_angle = [%f]\n", start_angle, g->rcd->angle);
	while (i < g->win_w)
	{
		if (i == 0)
			ray_angles[i] = start_angle * PI / 180;
		else
			ray_angles[i] = (start_angle + ((double)FOV / (double)g->win_w)) * (double)PI / (double)180;
		if (ray_angles[i] < 0)
			ray_angles[i] = ray_angles[i] + (2 * PI);
		else if (ray_angles[i] >= 2 * PI)
			ray_angles[i] = ray_angles[i] - (2 * PI);
		start_angle += ((double)FOV / (double)g->win_w);
		//start_angle += FOV / g->win_w;
		i++;
	}
}

void	calc_wall_dist(t_game *g, double ray_angle)
{
	double	actual_dist;

	actual_dist = sqrt(((g->rcd->tip_p->x - g->rcd->p_p->x) * (g->rcd->tip_p->x - g->rcd->p_p->x)) + 
	      			((g->rcd->tip_p->y - g->rcd->p_p->y) * (g->rcd->tip_p->y - g->rcd->p_p->y)));
	g->rcd->tip_dist = actual_dist * cos(ray_angle - g->rcd->angle);
}

void	draw_ceiling(t_game *g, int c_x, int cs_y, int ce_y)
{
	int	x;
	int	y;

	x = c_x;
	y = cs_y;
	while (y <= ce_y)
	{
		x = c_x;
		while (x < c_x + PX_SIZE)
		{
			if (y < g->minimap_h && x < g->minimap_w)
			{
				x++;
				continue ;
			}
			mlx_pixel_put(g->vars->mlx, g->vars->win, x, y, SKY);
			x++;
		}
		y++;
	}
}

void	draw_ground(t_game *g, int g_x, int gs_y, int ge_y)
{
	int	x;
	int	y;

	x = g_x;
	y = gs_y;
	while (y <= ge_y)
	{
		x = g_x;
		while (x < g_x + PX_SIZE)
		{
			mlx_pixel_put(g->vars->mlx, g->vars->win, x, y, GROUND);
			x++;
		}
		y++;
	}
}

void	draw_wall(t_game *g, int w_x, int ws_y, int we_y)
{
	int		x;
	int		y;
	int		tx_x;
	int		tx_y;
	double	progress;

	if (g->rcd->wall_type == HORIZONTAL)
		tx_x = (int)(g->rcd->tip_p->x) % CUBE_SIZE;
	else
		tx_x = (int)(g->rcd->tip_p->y) % CUBE_SIZE;
	y = ws_y;
	while (y <= we_y)
	{
		progress = (double)(y - ws_y) / (double)g->rcd->wall_height;
		//printf("progress = %f\n", progress);
		tx_y = (int)(progress * CUBE_SIZE - 1);
		if (tx_y < 0)
			tx_y = 0;
		else if (tx_y > 63)
			tx_y = 63;
		x = w_x;
		while (x < w_x + PX_SIZE)
		{
			if (y < g->minimap_h && x < g->minimap_w)
			{
				x++;
				continue ;
			}
			//if (x >= g->minimap_w && y >= g->minimap_h)
			mlx_pixel_put(g->vars->mlx, g->vars->win, x, y, g->chosen_tx[tx_y * CUBE_SIZE + tx_x]);
			//printf("width = %d\nheight = %d\n", g->minimap_w, g->minimap_h);
			x++;
		}
		y++;
	}
}

void	draw_stripe(t_game *g, int w_x, int ws_y, int we_y)
{
	int	x;
	int	y;
	//int	random_color;

	x = w_x;
	y = ws_y;
	//printf("x = [%d]\n", x);
	draw_ceiling(g, w_x, 0, ws_y);
	draw_wall(g, w_x, ws_y, we_y);
	/*while (y <= we_y)
	{
		x = w_x;
		//mlx_pixel_put(g->vars->mlx, g->vars->win, x, y, WHITE);
		while (x < w_x + PX_SIZE)
		{
			//printf("drawing at [%d, %d]\n", x, y);
			//random_color = rand() % 0xFFFFFF;
			mlx_pixel_put(g->vars->mlx, g->vars->win, x, y, WHITE);
			x++;
		}
		y++;
	}*/
	draw_ground(g, w_x, we_y, g->win_h);
}

void	choose_texture(t_game *g, double ray_angle)
{
	double	degree_angle;

	degree_angle = ray_angle * 180 / PI;
	if (g->rcd->wall_type == HORIZONTAL)
	{
		if (degree_angle >= 0 && degree_angle <= 180)
			g->chosen_tx = g->n_data;
		else if (degree_angle > 180 && degree_angle <= 360)
			g->chosen_tx = g->s_data;
	}
	else if (g->rcd->wall_type == VERTICAL)
	{
		if (cos(ray_angle) > 0)
			g->chosen_tx = g->w_data;
		else if (cos(ray_angle) < 0)
			g->chosen_tx = g->e_data;
	}
}

void	render_vision_ray(t_game *g)
{
	int		d_x;
	int		d_y;
	int		steps;
	int		i;
	double	*ray_angles;

	ray_angles = malloc(sizeof(double) * g->win_w);
	/*int	j = 0;
	while (j < g->win_w)
	{
		printf("ray_angle = [%f]\n", ray_angles[j]);
		j++;
	}
	exit(0);*/
	init_raycast_data(g);
	init_ray_angles(g, ray_angles);
	//printf("g player angle = %f\ng rcd angle = %f\n", g->player.angle, g->rcd->angle);
	//printf("player_dir = [%f]\nmid_ray = [%f]\n", g->rcd->angle, ray_angles[g->win_w / 4]);
	int	j = 0;
	while (j < g->win_w)
	{
		//printf("j = [%d]\n", j);
		get_horizontal_intercept(g, ray_angles[j]);
		get_vertical_intercept(g, ray_angles[j]);
		choose_ray_tip(g);
		choose_texture(g, ray_angles[j]);
		calc_wall_dist(g, ray_angles[j]);
		
		int	wall_height = (CUBE_SIZE * g->win_h) / g->rcd->tip_dist;
		int	wall_x = PX_SIZE;
		int	wall_start_y = (g->win_h / 2) - (wall_height / 2);
		int	wall_end_y = (g->win_h / 2) + (wall_height / 2);
		g->rcd->wall_height = wall_height;
		//printf("current ray = [%f]\n", ray_angles[j]);
		draw_stripe(g, j, wall_start_y, wall_end_y);
		/*d_x = g->rcd->tip_p->x - g->rcd->p_p->x;
		d_y = g->rcd->tip_p->y - g->rcd->p_p->y;
		
		if (abs(d_x) > abs(d_y))
			steps = abs(d_x);
		else
			steps = abs(d_y);
		
		i = 0;
		while (i <= steps)
		{
			render_ray_points(g->rcd->p_p->x + (i * d_x) / steps, 
							g->rcd->p_p->y + (i * d_y) / steps, g, PLAYER_COLOR);
			i++;
		}*/
		//render_point_debug(g, g->rcd->h_p->x, g->rcd->h_p->y, 0x0000FF);
		//render_point_debug(g, g->rcd->v_p->x, g->rcd->v_p->y, 0x008000);
		j += wall_x;
	}
	free(ray_angles);
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

	start_player_x = g->player.pos_x * MINIMAP_SIZE;
	start_player_y = g->player.pos_y * MINIMAP_SIZE;
	player_y = 0;
	while (player_y < PLAYER_SIZE)
	{
		player_x = 0;
		while (player_x < PLAYER_SIZE)
		{
			pixel_x = start_player_x + player_x - PLAYER_SIZE / 2;
			pixel_y = start_player_y + player_y - PLAYER_SIZE / 2;
			mlx_pixel_put(g->vars->mlx, g->vars->win, pixel_x, pixel_y, PLAYER_COLOR);
			//int	index = pixel_y * (g->img.line_len / 4) + pixel_x;
			//g->img.data[index] = PLAYER_COLOR;
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
				start_cube_x = map_x * MINIMAP_SIZE; 
				start_cube_y = map_y * MINIMAP_SIZE;
				// loop through the cube coordinates
				cube_y = 0;
				while (cube_y < MINIMAP_SIZE)
				{
					cube_x = 0;
					while (cube_x < MINIMAP_SIZE)
					{
						// calculate the current cube coordinates reached
						pixel_x = start_cube_x + cube_x;
						pixel_y = start_cube_y + cube_y;
						mlx_pixel_put(g->vars->mlx, g->vars->win, pixel_x, pixel_y, WHITE);
						// convert 2d coordinates to 1d coordinate
						//index = pixel_y * (g->img.line_len / 4) + pixel_x;
						//g->img.data[index] = WHITE;
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

int	isnt_wall(int c)
{
	return (c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

void	render_map_background(t_game *g)
{
	int		x;
	int		y;
	char	**map;

	y = 0;
	map = g->vars->p_data.matrix;
	while (y < g->minimap_h)
	{
		x = 0;
		while (x < g->minimap_w)
		{
			if (isnt_wall(map[y / MINIMAP_SIZE][x / MINIMAP_SIZE]))
				mlx_pixel_put(g->vars->mlx, g->vars->win, x, y, GROUND);
			x++;
		}
		y++;
	}
}

int	render(t_game *g)
{
	/*int	i;

	i = 0;
	while (i <= g->win_h * g->win_w)
	{
		g->img.data[i++] = BLACK;
	}*/
	render_map_background(g);
	render_map(g);
	render_player(g);
	render_vision_ray(g);
	//printf("player = [%f, %f]\n", g->player.pos_x, g->player.pos_y);
	//mlx_put_image_to_window(g->vars->mlx, g->vars->win, g->img.img, 0, 0);
}

void	cube_init(t_vars *vars)
{
	t_game	*g = gc_malloc(sizeof(t_game));
	int		width = CUBE_SIZE;
	int		height = CUBE_SIZE;

	g->vars = vars;
	//g->win_w = vars->p_data.width * 64;
	//g->win_h = vars->p_data.height * 64;
	g->win_w = 1000;
	g->win_h = 1000;
	g->minimap_w = g->vars->p_data.width * MINIMAP_SIZE;
	g->minimap_h = g->vars->p_data.height * MINIMAP_SIZE;
	printf("window dimensions = [%dx%d]\n", g->win_w, g->win_h);
	g->player.pos_x = (double) g->vars->p_data.p_x;
	g->player.pos_y = (double) g->vars->p_data.p_y;
	printf("parsed player direction = [%f]\n", g->vars->p_data.angle);
	g->player.angle = g->vars->p_data.angle;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, g->win_w, g->win_h, "Dungeon gayme");
	g->img.img = mlx_new_image(g->vars->mlx, g->win_w, g->win_h);
	g->img.data = (int *)mlx_get_data_addr(g->img.img, &g->img.bpp, &g->img.line_len, &g->img.endian);
	g->n_img = mlx_xpm_file_to_image(g->vars->mlx, g->vars->p_data.assets->north_wall, &width, &height);
	g->e_img = mlx_xpm_file_to_image(g->vars->mlx, g->vars->p_data.assets->east_wall, &width, &height);
	g->s_img = mlx_xpm_file_to_image(g->vars->mlx, g->vars->p_data.assets->south_wall, &width, &height);
	g->w_img = mlx_xpm_file_to_image(g->vars->mlx, g->vars->p_data.assets->west_wall, &width, &height);
	g->n_data = (int *)mlx_get_data_addr(g->n_img, &g->img.bpp, &g->img.line_len, &g->img.endian);
	g->e_data = (int *)mlx_get_data_addr(g->e_img, &g->img.bpp, &g->img.line_len, &g->img.endian);
	g->s_data = (int *)mlx_get_data_addr(g->s_img, &g->img.bpp, &g->img.line_len, &g->img.endian);
	g->w_data = (int *)mlx_get_data_addr(g->w_img, &g->img.bpp, &g->img.line_len, &g->img.endian);
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
	printf("parsed dimensions = [%d, %d]\n", vars.p_data.width, vars.p_data.height);
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
