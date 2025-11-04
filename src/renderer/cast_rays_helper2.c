/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:00:02 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/04 15:48:17 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	set_tip(t_pos *dst, t_pos *src,
			t_wall_type *wall_type_dst, t_wall_type wall_type)
{
	dst->x = src->x;
	dst->y = src->y;
	*wall_type_dst = wall_type;
}

void	strafe_right(t_game *g, double angle, int dir)
{
	double	x_step;
	double	y_step;

	x_step = g->player.pos_x + cos((PI / 2) + angle) * MOVE_SPEED;
	y_step = g->player.pos_y + sin((PI / 2) + angle) * MOVE_SPEED;
	if (check_new_position(x_step, y_step, g, dir))
	{
		g->player.pos_x = x_step;
		g->player.pos_y = y_step;
	}
}

void	strafe_left(t_game *g, double angle, int dir)
{
	double	x_step;
	double	y_step;

	x_step = g->player.pos_x + cos((PI / 2) - angle) * MOVE_SPEED;
	y_step = g->player.pos_y + sin((PI / 2) - angle) * MOVE_SPEED;
	if (check_new_position(x_step, y_step, g, dir))
	{
		g->player.pos_x = x_step;
		g->player.pos_y = y_step;
	}
}
