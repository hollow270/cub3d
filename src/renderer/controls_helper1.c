/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_helper1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:01:59 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/10 19:28:15 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	controls_helper1(int keycode, t_game *g)
{
	if (keycode == 'w' || keycode == 'd' || keycode == 's' || keycode == 'a')
		g->player.bob_time += 0.1;
	else
		g->player.bob_time *= 0.9;
	if (keycode == 101)
		use_door(g);
	if (keycode == 65307)
		return (close_game(g), 0);
	if (keycode == 109 && g->mouse_control == false)
	{
		mlx_mouse_hide(g->vars->mlx, g->vars->win);
		g->mouse_control = true;
		return (0);
	}
	else if (keycode == 109 && g->mouse_control == true)
	{
		mlx_mouse_show(g->vars->mlx, g->vars->win);
		g->mouse_control = false;
		return (0);
	}
	return (1);
}

void	controls_helper2(int keycode, t_game *g)
{
	double	angle;

	angle = g->player.angle * PI / 180;
	if (keycode == 'w')
		move_forward(g, angle);
	else if (keycode == 'd')
		strafe_right(g, angle);
	else if (keycode == 's')
		move_backward(g, angle);
	else if (keycode == 'a')
		strafe_left(g, angle);
}

void	move_forward(t_game *g, double angle)
{
	double	new_x;
	double	new_y;

	new_x = g->player.pos_x + cos(angle) * MOVE_SPEED;
	new_y = g->player.pos_y + sin(angle) * MOVE_SPEED;
	if (check_new_position(new_x, new_y, g))
	{
		g->player.pos_x = new_x;
		g->player.pos_y = new_y;
	}
	else if (check_new_position(new_x, g->player.pos_y, g))
		g->player.pos_x = new_x;
	else if (check_new_position(g->player.pos_x, new_y, g))
		g->player.pos_y = new_y;
}

void	move_backward(t_game *g, double angle)
{
	double	new_x;
	double	new_y;

	new_x = g->player.pos_x + cos(angle) * (-MOVE_SPEED);
	new_y = g->player.pos_y + sin(angle) * (-MOVE_SPEED);
	if (check_new_position(new_x, new_y, g))
	{
		g->player.pos_x = new_x;
		g->player.pos_y = new_y;
	}
	else if (check_new_position(new_x, g->player.pos_y, g))
		g->player.pos_x = new_x;
	else if (check_new_position(g->player.pos_x, new_y, g))
		g->player.pos_y = new_y;
}

int	check_new_position(double new_x, double new_y, t_game *g)
{
	t_collider	col;
	char		**map;

	col.start_x = new_x - COLLIDER_SZ;
	col.start_y = new_y - COLLIDER_SZ;
	col.max_x = new_x + COLLIDER_SZ;
	col.max_y = new_y + COLLIDER_SZ;
	col.y = col.start_y;
	map = g->vars->p_data.matrix;
	while (col.y < col.max_y)
	{
		col.x = col.start_x;
		while (col.x < col.max_x)
		{
			if (is_not_passable(map[(int)(col.y)][(int)(col.x)]))
				return (0);
			col.x += 0.05;
		}
		col.y += 0.05;
	}
	return (1);
}
