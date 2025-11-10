/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_outofbounds_floor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:07:47 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/10 16:08:04 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_outofbounds_floor(char **map, int x, int y)
{
	if (y == 0)
	{
		if ((int)ft_strlen(map[y + 1]) < x + 1)
			return (0);
	}
	else
	{
		if ((int)ft_strlen(map[y - 1]) < x + 1
			|| (int)ft_strlen(map[y + 1]) < x + 1)
			return (0);
	}
	return (1);
}
