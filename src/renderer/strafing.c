/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:45:52 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/10 19:39:51 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	strafe_right(t_game *g, double angle)
{
	double	x_step;
	double	y_step;

	x_step = g->player.pos_x + cos((PI / 2) + angle) * MOVE_SPEED;
	y_step = g->player.pos_y + sin((PI / 2) + angle) * MOVE_SPEED;
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

	x_step = g->player.pos_x - cos((PI / 2) + angle) * MOVE_SPEED;
	y_step = g->player.pos_y - sin((PI / 2) + angle) * MOVE_SPEED;
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
