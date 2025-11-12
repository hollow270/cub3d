/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:56:14 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/12 16:47:14 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
	init_keys(&g->keys);
	g->mouse_control = false;
	mlx_loop_hook(g->vars->mlx, render, g);
	mlx_hook(vars->win, KeyPress, KeyPressMask, key_press, g);
	mlx_hook(vars->win, KeyRelease, KeyReleaseMask, key_release, g);
	mlx_hook(vars->win, DestroyNotify, NoEventMask, close_game, g);
	mlx_hook(vars->win, MotionNotify, PointerMotionMask, pointer_motion, g);
	mlx_mouse_move(vars->mlx, vars->win, g->win_w / 2, g->win_h / 2);
	mlx_loop(vars->mlx);
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

void	init_keys(t_keys *keys)
{
	keys->w = false;
	keys->s = false;
	keys->d = false;
	keys->a = false;
	keys->left = false;
	keys->right = false;
}
