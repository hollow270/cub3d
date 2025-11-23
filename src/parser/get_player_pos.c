/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:50:59 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/04 19:51:12 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		check_map_chars(t_parse_data *p_data);
int		is_valid_char(int c);
int		is_player(int c);
double	get_player_direction(int c);

int	get_player_pos(t_parse_data *p_data)
{
	int		x;
	int		y;
	int		found;

	y = -1;
	found = 0;
	while (p_data->matrix[++y])
	{
		x = -1;
		while (p_data->matrix[y][++x])
		{
			if (is_player(p_data->matrix[y][x]) && found == 0)
			{
				p_data->p_x = (float)x + 0.5;
				p_data->p_y = (float)y + 0.5;
				p_data->angle = get_player_direction(p_data->matrix[y][x]);
				found++;
			}
			else if (is_player(p_data->matrix[y][x]) && found != 0)
				return (0);
		}
	}
	if (found == 0 || check_map_chars(p_data) == 0)
		return (0);
	return (1);
}

int	check_map_chars(t_parse_data *p_data)
{
	int		x;
	int		y;
	int		doors;
	char	**map;

	y = -1;
	map = p_data->matrix;
	doors = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (is_valid_char(map[y][x]) == 0)
				return (printf("culprit = %c\n", map[y][x]), 0);
			if (map[y][x] == 'D')
				doors++;
		}
	}
	if (doors > 0 && !p_data->has_door)
		return (0);
	else if (doors == 0 && p_data->has_door)
		return (0);
	return (1);
}

int	is_valid_char(int c)
{
	return (c == '1' || c == '0' || c == 'N'
		|| c == 'E' || c == 'S' || c == 'W'
		|| c == ' ' || c == 'D');
}

int	is_player(int c)
{
	return (c == 'N' || c == 'E' || c == 'S'
		|| c == 'W');
}

double	get_player_direction(int c)
{
	if (c == 'N')
		return ((double)270);
	if (c == 'E')
		return ((double)0);
	if (c == 'S')
		return ((double)90);
	if (c == 'W')
		return ((double)180);
	return (-1);
}
