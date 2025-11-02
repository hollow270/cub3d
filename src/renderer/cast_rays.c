/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 22:21:22 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/02 23:57:16 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	cast_rays(t_game *g, double ray_angle, int j)
{
	int	wall_height;
	int	wall_x;
	int	wall_start_y;
	int	wall_end_y;

	get_horizontal_intercept(g, g->rcd, ray_angle, 0);
	get_vertical_intercept(g, g->rcd, ray_angle, 0);
	choose_ray_tip(g);
	check_door_intercept(g);
	choose_texture(g, ray_angle);
	calc_wall_dist(g, ray_angle);
	wall_height = (CUBE_SIZE * g->win_h) / g->rcd->tip_dist;
	wall_x = PX_SIZE;
	wall_start_y = (g->win_h / 2) - (wall_height / 2);
	wall_end_y = (g->win_h / 2) + (wall_height / 2);
	g->rcd->wall_height = wall_height;
	draw_stripe(g, j, wall_start_y, wall_end_y);
}

void	get_horizontal_intercept(t_game *g, t_raycast *rcd,
			double angle, int flag)
{
	double	x_step;
	double	y_step;
	double	check_y;
	int		max_i;

	ghi_helper(g, rcd, angle, &y_step);
	rcd->h_p->x = rcd->p_p->x + ((rcd->h_p->y - rcd->p_p->y) / tan(angle));
	x_step = y_step / tan(angle);
	max_i = 100;
	while (max_i != 0)
	{
		check_y = rcd->h_p->y;
		if (y_step < 0)
			check_y -= 1;
		if (is_wall(g, rcd->h_p->x, check_y, flag))
			break ;
		rcd->h_p->x += x_step;
		rcd->h_p->y += y_step;
		max_i--;
	}
}

void	get_vertical_intercept(t_game *g, t_raycast *rcd,
			double angle, int flag)
{
	double	x_step;
	double	y_step;
	double	check_x;
	int		max_i;

	gvi_helper(g, rcd, angle, &x_step);
	rcd->v_p->y = rcd->p_p->y + ((rcd->v_p->x - rcd->p_p->x) * tan(angle));
	y_step = x_step * tan(angle);
	max_i = 100;
	while (max_i != 0)
	{
		check_x = rcd->v_p->x;
		if (x_step < 0)
			check_x -= 1;
		if (is_wall(g, check_x, rcd->v_p->y, flag))
			break ;
		rcd->v_p->x += x_step;
		rcd->v_p->y += y_step;
		max_i--;
	}
}

void	choose_ray_tip(t_game *g)
{
	double	h_dist;
	double	v_dist;

	h_dist = calc_dist(g->rcd->h_p, g->rcd->p_p);
	v_dist = calc_dist(g->rcd->v_p, g->rcd->p_p);
	if (h_dist == 0 || (v_dist != 0 && h_dist <= v_dist))
		set_tip(g->rcd->tip_p, g->rcd->h_p, &g->rcd->wall_type, HORIZONTAL);
	else
		set_tip(g->rcd->tip_p, g->rcd->v_p, &g->rcd->wall_type, VERTICAL);
}

void	choose_texture(t_game *g, double ray_angle)
{
	double	degree_angle;

	degree_angle = ray_angle * 180 / PI;
	if (g->rcd->is_door == 1)
		g->chosen_tx = g->d_data;
	else if (g->rcd->wall_type == HORIZONTAL)
	{
		if (degree_angle >= 0 && degree_angle <= 180)
			g->chosen_tx = g->n_data;
		else if (degree_angle > 180 && degree_angle <= 360)
			g->chosen_tx = g->s_data;
	}
	else if (g->rcd->wall_type == VERTICAL)
	{
		if (cos(ray_angle) > 0)
			g->chosen_tx = g->w_data;
		else if (cos(ray_angle) < 0)
			g->chosen_tx = g->e_data;
	}
}
