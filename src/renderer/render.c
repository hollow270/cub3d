/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 22:04:13 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/02 23:49:58 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_raycast_data(t_game *g)
{
	g->rcd = gc_malloc(sizeof(t_raycast));
	g->rcd->p_p = gc_malloc(sizeof(t_pos));
	g->rcd->p_p->x = g->player.pos_x * 64;
	g->rcd->p_p->y = g->player.pos_y * 64;
	g->rcd->angle = g->player.angle * PI / 180;
	g->rcd->h_p = gc_malloc(sizeof(t_pos));
	g->rcd->v_p = gc_malloc(sizeof(t_pos));
	g->rcd->tip_p = gc_malloc(sizeof(t_pos));
	g->rcd->tip_p->x = 0;
	g->rcd->tip_p->y = 0;
	g->rcd->is_door = 0;
}

void	init_raycast_data2(t_game *g)
{
	g->mrcd = gc_malloc(sizeof(t_raycast));
	g->mrcd->p_p = gc_malloc(sizeof(t_pos));
	g->mrcd->p_p->x = g->player.pos_x * 64;
	g->mrcd->p_p->y = g->player.pos_y * 64;
	g->mrcd->angle = g->player.angle * PI / 180;
	g->mrcd->h_p = gc_malloc(sizeof(t_pos));
	g->mrcd->v_p = gc_malloc(sizeof(t_pos));
	g->mrcd->tip_p = gc_malloc(sizeof(t_pos));
	g->mrcd->tip_p->x = 0;
	g->mrcd->tip_p->y = 0;
	g->mrcd->is_door = 0;
}

int	render(t_game *g)
{
	render_map_background(g);
	render_map(g);
	render_player(g);
	init_raycast_data(g);
	init_raycast_data2(g);
	g->ray_angles = gc_malloc(sizeof(double) * g->win_w);
	render_vision_ray(g);
	render_hell_yeah_pov(g);
	mlx_put_image_to_window(g->vars->mlx, g->vars->win, g->img.img, 0, 0);
	return (0);
}
