/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:04:04 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/03 00:01:15 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	close_game(t_game *g)
{
	if (g->vars->p_data.has_door)
		mlx_destroy_image(g->vars->mlx, g->d_img);
	mlx_destroy_image(g->vars->mlx, g->e_img);
	mlx_destroy_image(g->vars->mlx, g->n_img);
	mlx_destroy_image(g->vars->mlx, g->w_img);
	mlx_destroy_image(g->vars->mlx, g->s_img);
	mlx_destroy_image(g->vars->mlx, g->h_img);
	mlx_destroy_image(g->vars->mlx, g->img.img);
	mlx_destroy_window(g->vars->mlx, g->vars->win);
	mlx_destroy_display(g->vars->mlx);
	free(g->vars->mlx);
	gc_free_all();
	return (exit(0), 0);
}
