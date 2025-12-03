/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:10:45 by yhajbi            #+#    #+#             */
/*   Updated: 2025/12/03 17:39:15 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_map_line	*extract_assets(t_parse_data *p_data);
void		extract_color(t_parse_data *p_data, t_map_line *cur_line, int flag);
void		initialize_rgb(t_parse_data *p_data);
int			validate_values(char **values);

int	extract_data(t_parse_data *p_data)
{
	t_map_line	*line;

	p_data->assets = gc_malloc(sizeof(t_assets));
	if (!p_data->assets)
		return (0);
	line = p_data->map_lines;
	skip_leading_spaces(p_data);
	initialize_rgb(p_data);
	line = extract_assets(p_data);
	if (!line || !check_color_data(p_data->assets))
		return (printf("Error\nInvalid color data\n"), 0);
	p_data->assets->f_color = (p_data->assets->f_rgb[0] << 16)
		| (p_data->assets->f_rgb[1] << 8) | p_data->assets->f_rgb[2];
	p_data->assets->c_color = (p_data->assets->c_rgb[0] << 16)
		| (p_data->assets->c_rgb[1] << 8) | p_data->assets->c_rgb[2];
	p_data->assets->hell_yeah = ft_strdup("./assets/budweiser.xpm");
	return (1);
}

t_map_line	*extract_assets(t_parse_data *p_data)
{
	t_map_line	*node;

	node = p_data->map_lines;
	node = node->next;
	while (node && ft_strcmp(node->line, "MAP_START") != 0)
	{
		if (ft_strncmp("NO ", node->line, 3) == 0)
			p_data->assets->north_wall = (ft_split(node->line, ' ')[1]);
		else if (ft_strncmp("EA ", node->line, 3) == 0)
			p_data->assets->east_wall = ft_split(node->line, ' ')[1];
		else if (ft_strncmp("SO ", node->line, 3) == 0)
			p_data->assets->south_wall = ft_split(node->line, ' ')[1];
		else if (ft_strncmp("WE ", node->line, 3) == 0)
			p_data->assets->west_wall = ft_split(node->line, ' ')[1];
		else if (ft_strncmp("DO ", node->line, 3) == 0)
			p_data->assets->door = ft_split(node->line, ' ')[1];
		else if (ft_strncmp("C ", node->line, 2) == 0)
			extract_color(p_data, node, 1);
		else if (ft_strncmp("F ", node->line, 2) == 0)
			extract_color(p_data, node, 2);
		else
			return (printf("Error\nInvalid asset data\n"), NULL);
		node = node->next;
	}
	return (node);
}

void	extract_color(t_parse_data *p_data, t_map_line *cur_line, int flag)
{
	char	**values;
	int		i;

	values = ft_split(cur_line->line + 2, ',');
	if (ft_splitlen(values) != 3 || ft_charcount(cur_line->line + 2, ',') != 2)
		return ;
	if (validate_values(values) == 0)
	{
		p_data->is_valid = 0;
		return ;
	}
	i = -1;
	if (flag == 1)
	{
		while (values[++i])
			p_data->assets->c_rgb[i] = ft_atoi(values[i]);
	}
	else if (flag == 2)
	{
		while (values[++i])
			p_data->assets->f_rgb[i] = ft_atoi(values[i]);
	}
	return ;
}

void	initialize_rgb(t_parse_data *p_data)
{
	p_data->assets->c_rgb[0] = -1;
	p_data->assets->c_rgb[1] = -1;
	p_data->assets->c_rgb[2] = -1;
	p_data->assets->f_rgb[0] = -1;
	p_data->assets->f_rgb[1] = -1;
	p_data->assets->f_rgb[2] = -1;
}

int	validate_values(char **values)
{
	int	i;
	int	j;

	i = 0;
	while (values[i])
	{
		if (ft_atoi(values[i]) > 255 || ft_atoi(values[i]) < 0)
			return (printf("Error\nInvalid color values\n"), 0);
		j = 0;
		while (values[i][j])
		{
			if (values[i][j] < '0' || values[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
