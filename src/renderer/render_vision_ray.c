/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_vision_ray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 22:15:16 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/10 16:58:43 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	render_vision_ray(t_game *g)
{
	double	*ray_angles;
	int		j;

	save_middle_ray(g, &ray_angles);
	j = 0;
	while (j < g->win_w)
	{
		cast_rays(g, ray_angles[j], j);
		j += PX_SIZE;
	}
}

void	save_middle_ray(t_game *g, double **ray_angles)
{
	init_ray_angles(g, g->ray_angles);
	*ray_angles = g->ray_angles;
	get_horizontal_intercept(g, g->mrcd, (*ray_angles)[g->win_w / 2], 1);
	get_vertical_intercept(g, g->mrcd, (*ray_angles)[g->win_w / 2], 1);
	choose_ray_tip2(g);
	calc_wall_dist2(g, (*ray_angles)[g->win_w / 2]);
	/* printf("player [%f, %f]\npoint [%f, %f] at %f\n", g->player.pos_x, g->player.pos_y, g->mrcd->tip_p->x, */
	/* 	g->mrcd->tip_p->y, g->mrcd->tip_dist / CUBE_SIZE); */
}

void	init_ray_angles(t_game *g, double *ray_angles)
{
	int		i;
	double	start_angle;

	i = 0;
	start_angle = g->player.angle + (((double)FOV / 2) * -1);
	while (i < g->win_w)
	{
		if (i == 0)
			ray_angles[i] = start_angle * PI / 180;
		else
			ray_angles[i] = (start_angle + ((double)FOV
						/ (double)g->win_w)) * (double)PI / (double)180;
		if (ray_angles[i] < 0)
			ray_angles[i] = ray_angles[i] + (2 * PI);
		else if (ray_angles[i] >= 2 * PI)
			ray_angles[i] = ray_angles[i] - (2 * PI);
		start_angle += ((double)FOV / (double)g->win_w);
		i++;
	}
}

void	choose_ray_tip2(t_game *g)
{
	double	h_dist;
	double	v_dist;

	h_dist = calc_dist(g->mrcd->h_p, g->mrcd->p_p);
	v_dist = calc_dist(g->mrcd->v_p, g->mrcd->p_p);
	if (h_dist == 0 || (v_dist != 0 && h_dist <= v_dist))
		set_tip(g->mrcd->tip_p, g->mrcd->h_p, &g->mrcd->wall_type, HORIZONTAL);
	else
		set_tip(g->mrcd->tip_p, g->mrcd->v_p, &g->mrcd->wall_type, VERTICAL);
}

void	calc_wall_dist2(t_game *g, double ray_angle)
{
	double	actual_dist;

	actual_dist = sqrt(((g->mrcd->tip_p->x - g->mrcd->p_p->x)
				* (g->mrcd->tip_p->x - g->mrcd->p_p->x))
			+ ((g->mrcd->tip_p->y - g->mrcd->p_p->y)
				* (g->mrcd->tip_p->y - g->mrcd->p_p->y)));
	g->mrcd->tip_dist = actual_dist * cos(ray_angle - g->mrcd->angle);
}
