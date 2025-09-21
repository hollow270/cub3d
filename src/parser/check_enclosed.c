/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_enclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:42:13 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/21 15:38:44 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_enclosed_helper(char	**map, int x, int y, int in_spc);
int	count_height(char **map);
int	is_inner_char(int c);
int	count_width(char **map, int y);

int	check_enclosed(t_parse_data *p_data)
{
	int		x;
	int		y;
	int		in_spc;
	char	**map;

	y = 0;
	in_spc = 0;
	map = p_data->matrix;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (check_enclosed_helper(map, x, y, in_spc) == 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_enclosed_helper(char	**map, int x, int y, int in_spc)
{
	if (map[y][x] == ' ')
		in_spc = 1;
	else if (map[y][x] == '1' && in_spc == 1)
		in_spc = 0;
	else if (is_inner_char(map[y][x]) && in_spc == 1)
		return (0);
	else if (is_inner_char(map[y][x]) && y == 0)
		return (0);
	else if (is_inner_char(map[y][x]) && y == count_height(map) - 1) 
		return (0);
	else if (is_inner_char(map[y][x]) && in_spc == 1)
		return (0);
	else if (is_inner_char(map[y][x]) && map[y][x + 1] == ' ')
		return (0);
	else if (is_inner_char(map[y][x]) && x == 0)
		return (0);
	else if (is_inner_char(map[y][x]) && x == count_width(map, y) - 1)
		return (0);
	return (1);
}

int	count_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	is_inner_char(int c)
{
	return (c == '0' || c == 'N' || c == 'E' || c == 'S'
			|| c == 'W');
}

int	count_width(char **map, int y)
{
	int	x;

	x = 0;
	while (map[y][x])
		x++;
	return (x);
}
