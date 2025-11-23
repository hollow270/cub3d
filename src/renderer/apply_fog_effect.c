/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_fog_effect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:36:28 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/10 16:25:24 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	apply_fog_effect(int original_color, double distance)
{
	t_fog	fog;

	fog.r = (original_color >> 16) & 0xFF;
	fog.g = (original_color >> 8) & 0xFF;
	fog.b = original_color & 0xFF;
	if (distance < 300)
		return (original_color);
	fog.max_fog_distance = 1000.0;
	fog.fog_intensity = fmin((distance - 300) / fog.max_fog_distance, 1.0);
	fog.fog_r = 200;
	fog.fog_g = 200;
	fog.fog_b = 200;
	fog.final_r = (int)(fog.r * (1.0 - fog.fog_intensity)
			+ fog.fog_r * fog.fog_intensity);
	fog.final_g = (int)(fog.g * (1.0 - fog.fog_intensity)
			+ fog.fog_g * fog.fog_intensity);
	fog.final_b = (int)(fog.b * (1.0 - fog.fog_intensity)
			+ fog.fog_b * fog.fog_intensity);
	fog.final_r = fmin(fmax(fog.final_r, 0), 255);
	fog.final_g = fmin(fmax(fog.final_g, 0), 255);
	fog.final_b = fmin(fmax(fog.final_b, 0), 255);
	return ((fog.final_r << 16) | (fog.final_g << 8) | fog.final_b);
}
