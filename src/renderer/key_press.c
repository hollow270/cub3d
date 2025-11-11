/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:13:43 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/11 13:19:06 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	key_press(int keycode, t_game *g)
{
	if (keycode == 'w')
		g->keys.w = true;
	else if (keycode == 'a')
		g->keys.a = true;
	else if (keycode == 's')
		g->keys.s = true;
	else if (keycode == 'd')
		g->keys.d = true;
	else if (keycode == 65361 || keycode == 123)
		g->keys.left = true;
	else if (keycode == 65363 || keycode == 124)
		g->keys.right = true;
	else if (keycode == 65307)
		return (close_game(g), 0);
	else if (keycode == 101)
		use_door(g);
	else if (keycode == 109)
		manage_mouse_controls(g);
	return (0);
}

void	manage_mouse_controls(t_game *g)
{
	if (!g->mouse_control)
	{
		mlx_mouse_hide(g->vars->mlx, g->vars->win);
		g->mouse_control = true;
	}
	else
	{
		mlx_mouse_show(g->vars->mlx, g->vars->win);
		g->mouse_control = false;
	}
}

int	key_release(int keycode, t_game *g)
{
	if (keycode == 'w')
		g->keys.w = false;
	else if (keycode == 'a')
		g->keys.a = false;
	else if (keycode == 's')
		g->keys.s = false;
	else if (keycode == 'd')
		g->keys.d = false;
	else if (keycode == 65361 || keycode == 123)
		g->keys.left = false;
	else if (keycode == 65363 || keycode == 124)
		g->keys.right = false;
	return (0);
}
