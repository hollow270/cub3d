/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:45:52 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/11 13:29:16 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	strafe_right(t_game *g, double angle)
{
	double	x_step;
	double	y_step;
	double	div;

	div = 1;
	if (g->keys.w || g->keys.s)
		div = 2;
	x_step = g->player.pos_x + (cos((PI / 2) + angle) * MOVE_SPEED) / div;
	y_step = g->player.pos_y + (sin((PI / 2) + angle) * MOVE_SPEED) / div;
	if (check_new_position(x_step, y_step, g))
	{
		g->player.pos_x = x_step;
		g->player.pos_y = y_step;
	}
	else if (check_new_position(x_step, g->player.pos_y, g))
		g->player.pos_x = x_step;
	else if (check_new_position(g->player.pos_x, y_step, g))
		g->player.pos_y = y_step;
}

void	strafe_left(t_game *g, double angle)
{
	double	x_step;
	double	y_step;
	double	div;

	div = 1;
	if (g->keys.w || g->keys.s)
		div = 2;
	x_step = g->player.pos_x - (cos((PI / 2) + angle) * MOVE_SPEED) / div;
	y_step = g->player.pos_y - (sin((PI / 2) + angle) * MOVE_SPEED) / div;
	if (check_new_position(x_step, y_step, g))
	{
		g->player.pos_x = x_step;
		g->player.pos_y = y_step;
	}
	else if (check_new_position(x_step, g->player.pos_y, g))
		g->player.pos_x = x_step;
	else if (check_new_position(g->player.pos_x, y_step, g))
		g->player.pos_y = y_step;
}
