/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_file_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:37:45 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/06 15:28:48 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_map_line	*interpret_file_content(t_parse_data *p_data)
{
	int			txtr_found;
	t_map_line	*map_lines;
	int			i;
	int			limit;

	txtr_found = 0;
	map_lines = NULL;
	i = -1;
	add_line_node(&map_lines, create_line_node(ft_strdup("ASSETS")));
	limit = 6;
	while (p_data->file_content[++i])
	{
		if (ft_strstr(p_data->file_content[i], "DO "))
		{
			ifc_helper2(p_data, &map_lines, &limit, &i);
			continue ;
		}
		if (i == limit && !txtr_found)
			ifc_helper1(p_data, &map_lines, &txtr_found, i);
		else
			add_line_node(&map_lines,
				create_line_node(ft_strdup(p_data->file_content[i])));
		ifc_helper3(p_data, &map_lines, i);
	}
	return (map_lines);
}

t_map_line	*create_line_node(char *line)
{
	t_map_line	*ret;

	ret = gc_malloc(sizeof(t_map_line));
	ret->line = line;
	ret->next = NULL;
	return (ret);
}

void	add_line_node(t_map_line **map_lines, t_map_line *new)
{
	t_map_line	*head;
	t_map_line	*node;

	head = *map_lines;
	if (!*map_lines)
	{
		*map_lines = new;
		return ;
	}
	node = head;
	while (node->next)
		node = node->next;
	node->next = new;
}
