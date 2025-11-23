/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:50:12 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/10 16:29:47 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_mp_data(t_game *g, t_mp *mp);
void	draw_minimap(t_mp *mp);
void	draw_square(t_mp *mp, int gx, int gy);
void	draw_player(t_mp *mp);

void	render_minimap(t_game *g)
{
	t_mp	mp;

	init_mp_data(g, &mp);
	draw_minimap(&mp);
	draw_player(&mp);
}

void	init_mp_data(t_game *g, t_mp *mp)
{
	mp->g = g;
	mp->map = g->vars->p_data.matrix;
	mp->maxb_x = 100;
	mp->maxb_y = 100;
	mp->minb_x = 50;
	mp->minb_y = 50;
	mp->p_x = (mp->minb_x + mp->maxb_x) / 2;
	mp->p_y = (mp->minb_y + mp->maxb_y) / 2;
	mp->width_in_gcells = 7;
	mp->p_fx = g->player.pos_x;
	mp->p_fy = g->player.pos_y;
	mp->ming_x = (int)mp->p_fx - mp->width_in_gcells;
	mp->maxg_x = (int)mp->p_fx + mp->width_in_gcells;
	mp->ming_y = (int)mp->p_fy - mp->width_in_gcells;
	mp->maxg_y = (int)mp->p_fy + mp->width_in_gcells;
}

void	draw_minimap(t_mp *mp)
{
	int	gx;
	int	gy;

	gy = 0;
	while (mp->map[gy])
	{
		gx = 0;
		while (mp->map[gy][gx])
		{
			if (is_within_limits(mp, gx, gy))
				draw_square(mp, gx, gy);
			gx++;
		}
		gy++;
	}
}

void	draw_player(t_mp *mp)
{
	int	start_x;
	int	start_y;
	int	cube_x;
	int	cube_y;

	start_x = mp->p_x;
	start_y = mp->p_y;
	cube_y = 0;
	while (cube_y < MINIMAP_SIZE)
	{
		cube_x = 0;
		while (cube_x < MINIMAP_SIZE)
		{
			my_mlx_pixel_put(&mp->g->img, cube_x
				+ start_x, cube_y + start_y, PLAYER_COLOR);
			cube_x++;
		}
		cube_y++;
	}
}

void	draw_square(t_mp *mp, int gx, int gy)
{
	int	offset_x;
	int	offset_y;

	mp->gx = gx;
	mp->gy = gy;
	offset_x = gx - (int)mp->p_fx;
	offset_y = gy - (int)mp->p_fy;
	mp->sc_x = (mp->p_x + offset_x * MINIMAP_SIZE);
	mp->sc_y = (mp->p_y + offset_y * MINIMAP_SIZE);
	mp->cube_y = 0;
	while (mp->cube_y < MINIMAP_SIZE)
	{
		mp->cube_x = 0;
		while (mp->cube_x < MINIMAP_SIZE)
		{
			draw_pixel(mp);
			mp->cube_x++;
		}
		mp->cube_y++;
	}
}
