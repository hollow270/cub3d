/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_stripe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:26:11 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/08 00:19:43 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	apply_fog_effect(int original_color, double distance);
int	apply_exponential_fog(int original_color, double distance);

void	draw_stripe(t_game *g, int w_x, int ws_y, int we_y)
{
	draw_ceiling(g, w_x, 0, ws_y);
	draw_wall(g, w_x, ws_y, we_y);
	draw_ground(g, w_x, we_y, g->win_h);
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
			/* if (y < g->minimap_h && x < g->minimap_w) */
			/* { */
			/* 	x++; */
			/* 	continue ; */
			/* } */
			my_mlx_pixel_put(&g->img, x, y, g->c_rgb);
			x++;
		}
		y++;
	}
}

void	draw_wall(t_game *g, int w_x, int ws_y, int we_y)
{
	t_wall_ctx	wctx;

	if (g->rcd->wall_type == HORIZONTAL)
		wctx.tx_x = (int)(g->rcd->tip_p->x) % CUBE_SIZE;
	else
		wctx.tx_x = (int)(g->rcd->tip_p->y) % CUBE_SIZE;
	wctx.y = ws_y;
	while (wctx.y <= we_y)
	{
		draw_pixel_from_sprite(g, &wctx, w_x, ws_y);
		wctx.y++;
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
			my_mlx_pixel_put(&g->img, x, y, g->f_rgb);
			x++;
		}
		y++;
	}
}

void	draw_pixel_from_sprite(t_game *g, t_wall_ctx *wctx, int w_x, int ws_y)
{
	wctx->progress = (double)(wctx->y - ws_y) / (double)g->rcd->wall_height;
	wctx->tx_y = (int)(wctx->progress * CUBE_SIZE - 1);
	if (wctx->tx_y < 0)
		wctx->tx_y = 0;
	else if (wctx->tx_y > 63)
		wctx->tx_y = 63;

	int original_color = g->chosen_tx[wctx->tx_y * CUBE_SIZE + wctx->tx_x];
	
	// Apply fog effect
	int fogged_color = apply_fog_effect(original_color, g->rcd->tip_dist);
	/* int	fogged_color = apply_exponential_fog(original_color, g->rcd->tip_dist); */
	
	wctx->x = w_x;
	while (wctx->x < w_x + PX_SIZE)
	{
		/* if (wctx->y < g->minimap_h && wctx->x < g->minimap_w) */
		/* { */
		/* 	wctx->x++; */
		/* 	continue ; */
		/* } */
		/* my_mlx_pixel_put(&g->img, wctx->x, wctx->y, */
		/* 	g->chosen_tx[wctx->tx_y * CUBE_SIZE + wctx->tx_x]); */
		my_mlx_pixel_put(&g->img, wctx->x, wctx->y, fogged_color);
		wctx->x++;
	}
}

int	apply_fog_effect(int original_color, double distance)
{
	int	r = (original_color >> 16) & 0xFF;
	int	g = (original_color >> 8) & 0xFF;
	int	b = original_color & 0xFF;
	
	// Fog parameters - adjust these to your preference
	double max_fog_distance = 1700.0; // Distance at which fog is maximum
	double fog_intensity = fmin(distance / max_fog_distance, 1.0);
	
	// Fog color (light gray/white for lighter effect)
	int fog_r = 200;
	int fog_g = 200;
	int fog_b = 200;
	/* int fog_r = 0; */
	/* int fog_g = 0; */
	/* int fog_b = 0; */
	
	// Blend original color with fog color
	int final_r = (int)(r * (1.0 - fog_intensity) + fog_r * fog_intensity);
	int final_g = (int)(g * (1.0 - fog_intensity) + fog_g * fog_intensity);
	int final_b = (int)(b * (1.0 - fog_intensity) + fog_b * fog_intensity);
	
	// Clamp values
	final_r = fmin(fmax(final_r, 0), 255);
	final_g = fmin(fmax(final_g, 0), 255);
	final_b = fmin(fmax(final_b, 0), 255);
	
	return (final_r << 16) | (final_g << 8) | final_b;
}

int	apply_exponential_fog(int original_color, double distance)
{
	int	r = (original_color >> 16) & 0xFF;
	int	g = (original_color >> 8) & 0xFF;
	int	b = original_color & 0xFF;
	
	// Exponential fog parameters
	double fog_density = 0.1; // Adjust for thicker/thinner fog
	double fog_amount = 0.1 - exp(-distance * fog_density);
	
	// Fog color (light color for "lighter" effect)
	int fog_r = 220;
	int fog_g = 220;
	int fog_b = 220;
	
	int final_r = (int)(r * (1.0 - fog_amount) + fog_r * fog_amount);
	int final_g = (int)(g * (1.0 - fog_amount) + fog_g * fog_amount);
	int final_b = (int)(b * (1.0 - fog_amount) + fog_b * fog_amount);
	
	return (final_r << 16) | (final_g << 8) | final_b;
}
