/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 22:04:13 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/11 13:21:52 by yhajbi           ###   ########.fr       */
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
	init_raycast_data(g);
	init_raycast_data2(g);
	g->ray_angles = gc_malloc(sizeof(double) * g->win_w);
	scan_keys_status(g);
	render_vision_ray(g);
	render_hell_yeah_pov(g);
	render_minimap(g);
	mlx_put_image_to_window(g->vars->mlx, g->vars->win, g->img.img, 0, 0);
	return (0);
}

void	scan_keys_status(t_game *g)
{
	double	angle;

	angle = g->player.angle * PI / 180;
	if (g->keys.w)
		move_forward(g, angle);
	if (g->keys.s)
		move_backward(g, angle);
	if (g->keys.a)
		strafe_left(g, angle);
	if (g->keys.d)
		strafe_right(g, angle);
	scan_keys_rotate(g);
	if (g->keys.w || g->keys.s || g->keys.a || g->keys.d)
		g->player.bob_time += 0.1;
	else
		g->player.bob_time *= 0.9;
}

void	scan_keys_rotate(t_game *g)
{
	if (g->keys.left)
	{
		g->player.angle -= ROT_SPEED;
		if (g->player.angle < 0)
			g->player.angle += 360;
	}
	if (g->keys.right)
	{
		g->player.angle += ROT_SPEED;
		if (g->player.angle >= 360)
			g->player.angle -= 360;
	}
}
