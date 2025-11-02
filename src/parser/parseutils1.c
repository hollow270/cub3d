/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:31:42 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/01 19:15:05 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	skip_leading_spaces(t_parse_data *p_data)
{
	t_map_line	*node;

	node = p_data->map_lines->next;
	while (node && ft_strcmp(node->line, "MAP_START") != 0)
	{
		while (*node->line == ' ')
			node->line++;
		node = node->next;
	}
}

int	is_map(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '1'
			&& s[i] != '0' && s[i] != 'N'
			&& s[i] != 'E' && s[i] != 'S'
			&& s[i] != 'W' && s[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
