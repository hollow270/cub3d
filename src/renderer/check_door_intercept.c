/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_door_intercept.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:02:06 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/02 15:25:42 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	check_door_intercept(t_game *g)
{
	int		x;
	int		y;
	int		check_x;
	int		check_y;

	check_x = g->rcd->tip_p->x;
	check_y = g->rcd->tip_p->y;
	if (g->rcd->wall_type == HORIZONTAL
		&& g->rcd->p_p->y > g->rcd->tip_p->y)
		check_y -= 1;
	else if (g->rcd->wall_type == VERTICAL
		&& g->rcd->p_p->x > g->rcd->tip_p->x)
		check_x -= 1;
	x = check_x / CUBE_SIZE;
	y = check_y / CUBE_SIZE;
	if (x < 0 || x > g->vars->p_data.width)
		return ;
	else if (y < 0 || y > g->vars->p_data.height)
		return ;
	if (g->vars->p_data.matrix[y][x] == 'D')
		g->rcd->is_door = 1;
	else
		g->rcd->is_door = 0;
}
