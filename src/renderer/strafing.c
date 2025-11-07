/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:45:52 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/05 14:12:13 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

	x_step = g->player.pos_x - cos((PI / 2) + angle) * MOVE_SPEED;
	y_step = g->player.pos_y - sin((PI / 2) + angle) * MOVE_SPEED;
	if (check_new_position(x_step, y_step, g, dir))
	{
		g->player.pos_x = x_step;
		g->player.pos_y = y_step;
	}
}
