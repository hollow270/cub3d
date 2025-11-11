/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:56:14 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/11 11:30:49 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	key_press(int keycode, t_game *g)
{
	if (keycode == 'w')
		g->keys.w = true;
	else if (keycode == 'a')
		g->keys.a = true;
	else if (keycode == 's')
		g->keys.s = true;
	else if (keycode == 'd')
		g->keys.d = true;
	else if (keycode == 65361 || keycode == 123)
		g->keys.left = true;
	else if (keycode == 65363 || keycode == 124)
		g->keys.right = true;
	else if (keycode == 65307)
		return (close_game(g), 0);
	else if (keycode == 101)
		use_door(g);
	else if (keycode == 109)
	{
		if (!g->mouse_control)
		{
			mlx_mouse_hide(g->vars->mlx, g->vars->win);
			g->mouse_control = true;
		}
		else
		{
			mlx_mouse_show(g->vars->mlx, g->vars->win);
			g->mouse_control = false;
		}
	}
	return (0);
}

int	key_release(int keycode, t_game *g)
{
	if (keycode == 'w')
		g->keys.w = false;
	else if (keycode == 'a')
		g->keys.a = false;
	else if (keycode == 's')
		g->keys.s = false;
	else if (keycode == 'd')
		g->keys.d = false;
	else if (keycode == 65361 || keycode == 123)
		g->keys.left = false;
	else if (keycode == 65363 || keycode == 124)
		g->keys.right = false;
	return (0);
}

void	cube_init(t_vars *vars)
{
	t_game	*g;

	g = gc_malloc(sizeof(t_game));
	init_game_data(g, vars);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx,
			g->win_w, g->win_h, "Hell Yeah Simulator");
	g->img.img = mlx_new_image(g->vars->mlx, g->win_w, g->win_h);
	g->img.data = (int *)mlx_get_data_addr(g->img.img,
			&g->img.bpp, &g->img.line_len, &g->img.endian);
	init_sprites(g);
	memset(&g->keys, 0, sizeof(t_keys)); // remove later
	g->mouse_control = false;
	mlx_loop_hook(g->vars->mlx, render, g);
	/* mlx_hook(vars->win, KeyPress, KeyPressMask, controls, g); */
	mlx_hook(vars->win, KeyPress, KeyPressMask, key_press, g);
	mlx_hook(vars->win, KeyRelease, KeyReleaseMask, key_release, g);
	mlx_hook(vars->win, DestroyNotify, NoEventMask, close_game, g);
	mlx_hook(vars->win, MotionNotify, PointerMotionMask, pointer_motion, g);
	mlx_mouse_move(vars->mlx, vars->win, g->win_w / 2, g->win_h / 2);
	mlx_loop(vars->mlx);
	render(g);
}

void	init_game_data(t_game *g, t_vars *vars)
{
	g->vars = vars;
	g->win_w = WIN_W;
	g->win_h = WIN_H;
	g->minimap_w = g->vars->p_data.width * MINIMAP_SIZE;
	g->minimap_h = g->vars->p_data.height * MINIMAP_SIZE;
	g->player.pos_x = (double) g->vars->p_data.p_x;
	g->player.pos_y = (double) g->vars->p_data.p_y;
	g->player.bob_time = 0;
	g->player.bob_amplitude = 16;
	g->player.bob_frequency = 2;
	g->player.angle = g->vars->p_data.angle;
	g->f_rgb = vars->p_data.assets->f_color;
	g->c_rgb = vars->p_data.assets->c_color;
}

void	init_sprites(t_game *g)
{
	int	width;
	int	height;
	int	h_width;
	int	h_height;

	g->n_img = mlx_xpm_file_to_image(g->vars->mlx,
			g->vars->p_data.assets->north_wall, &width, &height);
	g->e_img = mlx_xpm_file_to_image(g->vars->mlx,
			g->vars->p_data.assets->east_wall, &width, &height);
	g->s_img = mlx_xpm_file_to_image(g->vars->mlx,
			g->vars->p_data.assets->south_wall, &width, &height);
	g->w_img = mlx_xpm_file_to_image(g->vars->mlx,
			g->vars->p_data.assets->west_wall, &width, &height);
	if (g->vars->p_data.has_door)
		g->d_img = mlx_xpm_file_to_image(g->vars->mlx,
				g->vars->p_data.assets->door, &width, &height);
	g->h_img = mlx_xpm_file_to_image(g->vars->mlx,
			HELL_YEAH, &h_width, &h_height);
	init_data_addresses(g);
}

void	init_data_addresses(t_game *g)
{
	g->n_data = (int *)mlx_get_data_addr(g->n_img,
			&g->img.bpp, &g->img.line_len, &g->img.endian);
	g->e_data = (int *)mlx_get_data_addr(g->e_img,
			&g->img.bpp, &g->img.line_len, &g->img.endian);
	g->s_data = (int *)mlx_get_data_addr(g->s_img,
			&g->img.bpp, &g->img.line_len, &g->img.endian);
	g->w_data = (int *)mlx_get_data_addr(g->w_img,
			&g->img.bpp, &g->img.line_len, &g->img.endian);
	if (g->vars->p_data.has_door)
		g->d_data = (int *)mlx_get_data_addr(g->d_img,
				&g->img.bpp, &g->img.line_len, &g->img.endian);
	g->h_data = (int *)mlx_get_data_addr(g->h_img,
			&g->img.bpp, &g->img.line_len, &g->img.endian);
}
