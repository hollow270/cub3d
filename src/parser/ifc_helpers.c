/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifc_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 19:09:00 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/01 19:35:51 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ifc_helper1(t_parse_data *p_data,
				t_map_line **map_lines, int *txtr_found, int i)
{
	add_line_node(map_lines, create_line_node(ft_strdup("MAP_START")));
	add_line_node(map_lines,
		create_line_node(ft_strdup(p_data->file_content[i])));
	*txtr_found = 1;
}

void	ifc_helper2(t_parse_data *p_data,
				t_map_line **map_lines, int *limit, int *i)
{
	add_line_node(map_lines,
		create_line_node(ft_strdup(p_data->file_content[*i])));
	p_data->has_door = 1;
	*i = *i + 1;
	*limit = 7;
}

void	ifc_helper3(t_parse_data *p_data,
				t_map_line **map_lines, int i)
{
	if (!p_data->file_content[i + 1])
		add_line_node(map_lines, create_line_node(ft_strdup("MAP_END")));
}
