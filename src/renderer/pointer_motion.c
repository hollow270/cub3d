/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_motion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:07:36 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/03 00:02:00 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	pointer_motion(int x, int y, t_game *g)
{
	static int	first_motion = 1;
	int			center_x;
	int			center_y;
	int			diff;

	center_x = g->win_w / 2;
	center_y = g->win_h / 2;
	if (g->mouse_control == 0)
		return (0);
	if (first_motion)
	{
		first_motion = 0;
		mlx_mouse_move(g->vars->mlx, g->vars->win, center_x, center_y);
		return (0);
	}
	diff = x - center_x;
	g->player.angle += diff * 0.05;
	if (g->player.angle < 0)
		g->player.angle += 360;
	else if (g->player.angle >= 360)
		g->player.angle -= 360;
	mlx_mouse_move(g->vars->mlx, g->vars->win, center_x, center_y);
	return (0);
}
