/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hell_yeah_pov.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 22:17:21 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/02 23:56:55 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	render_hell_yeah_pov(t_game *g)
{
	int		image_x;
	int		image_y;
	int		offset_y;
	int		source_pixel;
	double	bob_offset;

	bob_offset = g->player.bob_amplitude
		* sin(g->player.bob_frequency * g->player.bob_time);
	offset_y = (int)bob_offset;
	image_y = 0;
	while (image_y < 1000)
	{
		image_x = 0;
		while (image_x < 1000)
		{
			source_pixel = g->h_data[image_y * 1000 + image_x];
			if (source_pixel != -16777216)
				my_mlx_pixel_put(&g->img, image_x, image_y
					+ offset_y, source_pixel);
			image_x++;
		}
		image_y++;
	}
}
