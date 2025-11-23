/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:59:15 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/03 00:01:55 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	controls(int keycode, t_game *g)
{
	if (controls_helper1(keycode, g) == 0)
		return (0);
	controls_helper2(keycode, g);
	if (keycode == 65361 || keycode == 123)
	{
		g->player.angle -= ROT_SPEED;
		if (g->player.angle < 0)
			g->player.angle += 360;
	}
	else if (keycode == 65363 || keycode == 124)
	{
		g->player.angle += ROT_SPEED;
		if (g->player.angle >= 360)
			g->player.angle -= 360;
	}
	return (0);
}
