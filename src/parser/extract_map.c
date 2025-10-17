/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:20:25 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/20 19:51:56 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	calculate_height(t_map_line *map);

char	**extract_map(t_parse_data *p_data)
{
	int			i;
	int			height;
	char		**ret;
	t_map_line	*node;

	node = p_data->map_lines;
	while (ft_strcmp("MAP_START", node->line) != 0)
		node = node->next;
	node = node->next;
	height = calculate_height(node);
	ret = gc_malloc(sizeof(char *) * (height + 1));
	i = 0;
	while (node && ft_strcmp(node->line, "MAP_END") != 0)
	{
		ret[i] = ft_strdup(node->line);
		node = node->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	calculate_height(t_map_line *map)
{
	int			count;
	t_map_line	*node;

	count = 0;
	node = map;
	while (node && ft_strcmp(node->line, "MAP_END") != 0)
	{
		count++;
		node = node->next;
	}
	return (count);
}
