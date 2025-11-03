/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:40:09 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/03 18:08:26 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	use_door(t_game *g)
{
	int			map_x;
	int			map_y;

	map_x = g->mrcd->tip_p->x;
	map_y = g->mrcd->tip_p->y;
	if (g->mrcd->wall_type == HORIZONTAL && g->rcd->p_p->y > g->mrcd->tip_p->y)
		map_y -= 1;
	else if (g->mrcd->wall_type == VERTICAL
		&& g->rcd->p_p->x > g->mrcd->tip_p->x)
		map_x -= 1;
	map_x = map_x / CUBE_SIZE;
	map_y = map_y / CUBE_SIZE;
	if (map_x < 0)
		map_x = 0;
	else if (map_x > g->vars->p_data.width)
		map_x = g->vars->p_data.width;
	if (map_y < 0)
		map_y = 0;
	else if (map_y > g->vars->p_data.height)
		map_y = g->vars->p_data.height;
	set_door_status(g, g->vars->p_data.matrix, map_x, map_y);
}

void	set_door_status(t_game *g, char **map, int x, int y)
{
	if (map[y][x] == 'D' && g->mrcd->tip_dist < DOOR_OPEN_DIST)
		map[y][x] = 'O';
	else if (map[y][x] == 'O' && g->mrcd->tip_dist < DOOR_OPEN_DIST)
		map[y][x] = 'D';
}
