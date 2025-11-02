/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 22:10:41 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/03 00:00:15 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	render_map(t_game *g)
{
	t_minimap	mp;

	mp.map_y = 0;
	mp.map = g->vars->p_data.matrix;
	while (mp.map[mp.map_y])
	{
		mp.map_x = 0;
		while (mp.map[mp.map_y][mp.map_x])
		{
			if (mp.map[mp.map_y][mp.map_x] == '1'
				|| mp.map[mp.map_y][mp.map_x] == 'D'
				|| mp.map[mp.map_y][mp.map_x] == 'O')
			{
				mp.start_cube_x = mp.map_x * MINIMAP_SIZE;
				mp.start_cube_y = mp.map_y * MINIMAP_SIZE;
				mp.cube_y = 0;
				draw_mp_square(g, &mp);
			}
			mp.map_x++;
		}
		mp.map_y++;
	}
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
				my_mlx_pixel_put(&g->img, x, y, GROUND);
			x++;
		}
		y++;
	}
}

void	render_player(t_game *g)
{
	t_player_mp	pmp;

	pmp.map = g->vars->p_data.matrix;
	pmp.start_player_x = g->player.pos_x * MINIMAP_SIZE;
	pmp.start_player_y = g->player.pos_y * MINIMAP_SIZE;
	pmp.player_y = 0;
	while (pmp.player_y < PLAYER_SIZE)
	{
		pmp.player_x = 0;
		while (pmp.player_x < PLAYER_SIZE)
		{
			pmp.pixel_x = pmp.start_player_x + pmp.player_x - PLAYER_SIZE / 2;
			pmp.pixel_y = pmp.start_player_y + pmp.player_y - PLAYER_SIZE / 2;
			my_mlx_pixel_put(&g->img, pmp.pixel_x, pmp.pixel_y, PLAYER_COLOR);
			pmp.player_x++;
		}
		pmp.player_y++;
	}
}

void	draw_mp_square(t_game *g, t_minimap *mp)
{
	while (mp->cube_y < MINIMAP_SIZE)
	{
		mp->cube_x = 0;
		while (mp->cube_x < MINIMAP_SIZE)
		{
			draw_mp_pixel(g, mp);
			mp->cube_x++;
		}
		mp->cube_y++;
	}
}

void	draw_mp_pixel(t_game *g, t_minimap *mp)
{
	mp->pixel_x = mp->start_cube_x + mp->cube_x;
	mp->pixel_y = mp->start_cube_y + mp->cube_y;
	if (mp->map[mp->map_y][mp->map_x] == 'D')
		my_mlx_pixel_put(&g->img, mp->pixel_x, mp->pixel_y, BROWN);
	else if (mp->map[mp->map_y][mp->map_x] == 'O')
		my_mlx_pixel_put(&g->img, mp->pixel_x, mp->pixel_y, GROUND);
	else
		my_mlx_pixel_put(&g->img, mp->pixel_x, mp->pixel_y, WHITE);
}
