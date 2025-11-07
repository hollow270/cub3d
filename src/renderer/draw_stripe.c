/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_stripe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:26:11 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/06 10:58:58 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
			if (y < g->minimap_h && x < g->minimap_w)
			{
				x++;
				continue ;
			}
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
	wctx->x = w_x;
	while (wctx->x < w_x + PX_SIZE)
	{
		if (wctx->y < g->minimap_h && wctx->x < g->minimap_w)
		{
			wctx->x++;
			continue ;
		}
		my_mlx_pixel_put(&g->img, wctx->x, wctx->y,
			g->chosen_tx[wctx->tx_y * CUBE_SIZE + wctx->tx_x]);
		wctx->x++;
	}
}
