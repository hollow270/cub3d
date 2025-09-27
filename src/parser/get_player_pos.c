/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:50:59 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/27 10:35:51 by yhajbi           ###   ########.fr       */
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
	char	**map;

	if (check_map_chars(p_data) == 0)
		return (0);
	map = p_data->matrix;
	y = 0;
	found = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player(map[y][x]) && found == 0)
			{
				p_data->p_x = (float)x + 0.5;
				p_data->p_y = (float)y + 0.5;
				p_data->angle = get_player_direction(map[y][x]);
				found++;
			}
			else if (is_player(map[y][x]) && found != 0)
				return (0);
			x++;
		}
		y++;
	}
	if (found == 0)
		return (0);
	return (1);
}

int	check_map_chars(t_parse_data *p_data)
{
	int		x;
	int		y;
	char	**map;

	y = 0;
	map = p_data->matrix;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_valid_char(map[y][x]) == 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	is_valid_char(int c)
{
	return (c == '1' || c == '0' || c == 'N'
			|| c == 'E' || c == 'S' || c == 'W');
}

int	is_player(int c)
{
	return (c == 'N' || c == 'E' || c == 'S'
			|| c == 'W');
}

double	get_player_direction(int c)
{
	if (c == 'N')
		return ((double)90 + 180);
	if (c == 'E')
		return ((double)0 + 180);
	if (c == 'S')
		return ((double)270 + 180);
	if (c == 'W')
		return ((double)180 + 180);
	return (-1);
}
