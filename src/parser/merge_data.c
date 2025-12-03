/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:37:38 by yhajbi            #+#    #+#             */
/*   Updated: 2025/12/03 19:30:58 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	merge_data(t_parse_data p_data, t_game *g)
{
	/* g->player.x = (double)p_data.p_x; */
	/* g->player.y = (double)p_data.p_y; */

	/*
	* g->player.dir_x
	* g->player.dir_y
	* g->player.plane_x
	* g->player.plane_y
	*/

	/* g->map_w = p_data.width; */
	/* g->map_h = p_data.height; */
	/* g->map = p_data.matrix; */
	/**/
	/* g->ceiling = p_data.assets->c_color; */
	/* g->floor = p_data.assets->f_color; */
	/**/
	/* g->tex_path[TEX_N] = p_data.assets->north_wall; */
	/* g->tex_path[TEX_E] = p_data.assets->east_wall; */
	/* g->tex_path[TEX_S] = p_data.assets->south_wall; */
	/* g->tex_path[TEX_W] = p_data.assets->west_wall; */
	/**/
	/* g->door_path = p_data.assets->door; */
	// Zero out the game struct first to be safe
	/* ft_memset(g, 0, sizeof(t_game)); */

	// 1. Player Position (+0.5 to center in tile)
	g->player.x = (double)p_data.p_x + 0.5;
	g->player.y = (double)p_data.p_y + 0.5;

	// 2. Player Direction (Math Required!)
	// Your parser has 'angle' (radians). His raycaster needs vectors.
	g->player.dir_x = -cos(p_data.angle);
	g->player.dir_y = -sin(p_data.angle);

	// 3. Camera Plane (FOV)
	// Perpendicular to direction. 0.66 is standard for ~66 fov
	g->player.plane_x = -g->player.dir_y * 0.66;
	g->player.plane_y = g->player.dir_x * 0.66;

	// 4. Map
	g->map_w = p_data.width;
	g->map_h = p_data.height;
	g->map = p_data.matrix; // Direct pointer assignment (Shallow copy)

	// 5. Colors
	g->ceiling = p_data.assets->c_color;
	g->floor = p_data.assets->f_color;

	// 6. Textures
	g->tex_path[TEX_N] = p_data.assets->north_wall;
	g->tex_path[TEX_E] = p_data.assets->east_wall;
	g->tex_path[TEX_S] = p_data.assets->south_wall;
	g->tex_path[TEX_W] = p_data.assets->west_wall;
	
	// 7. Bonus Assets
	g->door_path = p_data.assets->door;
	// Use the 'hell_yeah' texture for the hand/weapon
	g->hand_path = p_data.assets->hell_yeah; 
	g->hand_phase = 0; // Reset animation
}
