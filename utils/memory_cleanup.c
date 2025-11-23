/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:03:24 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/01 21:52:46 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_map_lines(t_map_line *head)
{
	t_map_line	*node;
	t_map_line	*cup;

	node = head;
	while (node)
	{
		cup = node->next;
		free(node);
		node = cup;
	}
}
