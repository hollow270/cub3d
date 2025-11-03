/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_helper1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:54:14 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/03 18:06:58 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	calc_wall_dist(t_game *g, double ray_angle)
{
	double	actual_dist;

	actual_dist = sqrt(((g->rcd->tip_p->x - g->rcd->p_p->x)
				* (g->rcd->tip_p->x - g->rcd->p_p->x))
			+ ((g->rcd->tip_p->y - g->rcd->p_p->y)
				* (g->rcd->tip_p->y - g->rcd->p_p->y)));
	g->rcd->tip_dist = actual_dist * cos(ray_angle - g->rcd->angle);
}

void	ghi_helper(t_raycast *rcd, double angle, double *y_step)
{
	if (fabs(sin(angle)) < 0.0001)
	{
		rcd->h_p->x = rcd->p_p->x;
		rcd->h_p->y = rcd->p_p->y;
		return ;
	}
	if (angle > PI)
	{
		rcd->h_p->y = floor(rcd->p_p->y / 64) * 64;
		if (rcd->h_p->y == rcd->p_p->y)
			rcd->h_p->y -= 64;
		*y_step = -64;
	}
	else
	{
		rcd->h_p->y = ceil(rcd->p_p->y / 64) * 64;
		if (rcd->h_p->y == rcd->p_p->y)
			rcd->h_p->y += 64;
		*y_step = 64;
	}
}

void	gvi_helper(t_raycast *rcd, double angle, double *x_step)
{
	if (fabs(cos(angle)) < 0.0001)
	{
		rcd->v_p->x = rcd->p_p->x;
		rcd->v_p->y = rcd->p_p->y;
		return ;
	}
	if (cos(angle) > 0)
	{
		rcd->v_p->x = ceil(rcd->p_p->x / 64) * 64;
		if (rcd->v_p->x == rcd->p_p->x)
			rcd->v_p->x += 64;
		*x_step = 64;
	}
	else
	{
		rcd->v_p->x = floor(rcd->p_p->x / 64) * 64;
		if (rcd->v_p->x == rcd->p_p->x)
			rcd->v_p->x -= 64;
		*x_step = -64;
	}
}

int	is_wall(t_game *g, double x, double y, int flag)
{
	char	**map;
	int		map_x;
	int		map_y;
	int		width;
	int		height;

	map_x = (int)x / 64;
	map_y = (int)y / 64;
	width = g->vars->p_data.width;
	height = g->vars->p_data.height;
	if (map_x < 0 || map_x >= width || map_y < 0 || map_y >= height)
		return (1);
	map = g->vars->p_data.matrix;
	if (flag == 0)
	{
		if (map[map_y][map_x] == '1' || map[map_y][map_x] == 'D')
			return (1);
	}
	else
	{
		if (map[map_y][map_x] == '1' || map[map_y][map_x] == 'D'
			|| map[map_y][map_x] == 'O')
			return (1);
	}
	return (0);
}

double	calc_dist(t_pos *p1, t_pos *p2)
{
	double	dx;
	double	dy;

	dx = p1->x - p2->x;
	dy = p1->y - p2->y;
	return (sqrt(dx * dx + dy * dy));
}
