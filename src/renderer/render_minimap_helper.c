/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:28:58 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/10 22:21:07 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_pixel(t_mp *mp)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = mp->sc_x + mp->cube_x;
	pixel_y = mp->sc_y + mp->cube_y;
	if (mp->map[mp->gy][mp->gx] != '1')
		my_mlx_pixel_put(&mp->g->img, pixel_x, pixel_y, BLACK);
	/* if (mp->map[mp->gy][mp->gx] == 'D') */
	/* 	my_mlx_pixel_put(&mp->g->img, pixel_x, pixel_y, WHITE); */
	/* else if (mp->map[mp->gy][mp->gx] == '0') */
	/* 	my_mlx_pixel_put(&mp->g->img, pixel_x, pixel_y, BLACK); */
	/* else if (mp->map[mp->gy][mp->gx] == 'O') */
	/* 	my_mlx_pixel_put(&mp->g->img, pixel_x, pixel_y, BLACK); */
	/* else if (mp->map[mp->gy][mp->gx] == 'N') */
	/* 	my_mlx_pixel_put(&mp->g->img, pixel_x, pixel_y, BLACK); */
	/* else if (mp->map[mp->gy][mp->gx] == 'E') */
	/* 	my_mlx_pixel_put(&mp->g->img, pixel_x, pixel_y, BLACK); */
	/* else if (mp->map[mp->gy][mp->gx] == 'S') */
	/* 	my_mlx_pixel_put(&mp->g->img, pixel_x, pixel_y, BLACK); */
	/* else if (mp->map[mp->gy][mp->gx] == 'W') */
	/* 	my_mlx_pixel_put(&mp->g->img, pixel_x, pixel_y, BLACK); */
	/* else if (mp->map[mp->gy][mp->gx] == '1') */
	/* 	my_mlx_pixel_put(&mp->g->img, pixel_x, pixel_y, WHITE); */
	/* else */
	/* 	my_mlx_pixel_put(&mp->g->img, pixel_x, pixel_y, GROUND); */
}

int	is_within_limits(t_mp *mp, int x, int y)
{
	if (y < 0 || y >= mp->g->vars->p_data.height
		|| x < 0 || x > mp->g->vars->p_data.width)
		return (0);
	else if (x < mp->ming_x || x > mp->maxg_x)
		return (0);
	else if (y < mp->ming_y || y > mp->maxg_y)
		return (0);
	return (1);
}
