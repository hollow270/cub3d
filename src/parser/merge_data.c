/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:37:38 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/28 15:02:32 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	merge_data(t_parse_data p_data, t_game *g)
{
	g->player.x = (double)p_data.p_x;
	g->player.y = (double)p_data.p_y;

	/*
	* g->player.dir_x
	* g->player.dir_y
	* g->player.plane_x
	* g->player.plane_y
	*/

	g->map_w = p_data.width;
	g->map_h = p_data.height;
	g->map = p_data.matrix;

	g->ceiling = p_data.assets->c_color;
	g->floor = p_data.assets->f_color;

	g->tex_path[TEX_N] = p_data.assets->north_wall;
	g->tex_path[TEX_E] = p_data.assets->east_wall;
	g->tex_path[TEX_S] = p_data.assets->south_wall;
	g->tex_path[TEX_W] = p_data.assets->west_wall;

	g->door_path = p_data.assets->door;
}
