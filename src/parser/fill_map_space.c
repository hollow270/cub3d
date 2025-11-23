/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:12:36 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/12 16:50:40 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		get_max_width(t_parse_data *p_data);
void	add_walls(char **s, int max_x);
void	get_map_dimensions(t_parse_data *p_data);

void	fill_map_space(t_parse_data *p_data)
{
	int		max_x;
	int		x;
	int		y;
	char	**map;

	max_x = get_max_width(p_data);
	y = 0;
	map = p_data->matrix;
	while (map[y])
	{
		if ((int)(ft_strlen(map[y])) < max_x)
			add_walls(&map[y], max_x);
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ' ')
				map[y][x] = '1';
			x++;
		}
		y++;
	}
	get_map_dimensions(p_data);
}

int	get_max_width(t_parse_data *p_data)
{
	int		max_width;
	int		current_width;
	int		y;
	char	**map;

	max_width = 0;
	current_width = 0;
	y = 0;
	map = p_data->matrix;
	while (map[y])
	{
		current_width = ft_strlen(map[y]);
		if (current_width > max_width)
			max_width = current_width;
		y++;
	}
	return (max_width);
}

void	add_walls(char **s, int max_x)
{
	int		walls;
	char	*new;
	int		i;

	walls = max_x - ft_strlen(*s);
	new = gc_malloc(sizeof(char) * ft_strlen(*s) + walls + 1);
	ft_strlcpy(new, *s, ft_strlen(*s) + walls + 1);
	i = ft_strlen(*s);
	while (walls)
	{
		new[i++] = '1';
		walls--;
	}
	new[i] = '\0';
	*s = new;
}

void	get_map_dimensions(t_parse_data *p_data)
{
	int	x;
	int	y;

	y = 0;
	while (p_data->matrix[y])
	{
		x = 0;
		while (p_data->matrix[y][x])
			x++;
		y++;
	}
	p_data->height = y;
	p_data->width = x;
}
