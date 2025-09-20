/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:56:03 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/18 13:29:04 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* ft_calculate_length:
 * Calculates the total length of the line
 * that should be returned by adding the
 * size of each fragment, then adding up
 * to \n of the very last fragment
 * (including the \n, by doing length++
 * before checking if we reached the \n) */

static size_t	ft_calc_len(t_fragment *p_head)
{
	ssize_t		i;
	ssize_t		sum;
	t_fragment	*node;

	sum = 0;
	node = p_head;
	while (node->stop == 0)
	{
		sum += node->sz;
		node = node->next;
	}
	i = 0;
	while (i < node->sz)
	{
		sum++;
		if (node->fragment[i] == '\n')
			break ;
		i++;
	}
	return (sum);
}

/* ft_excess:
 * Copies up to the \n to the end of the returning line
 * (including the line by copying then checking if a nl
 * was copied) i++ to add the \0 and j++ to copy the
 * excess after the \n to the head's fragment. Then
 * setting the head->size to how much was copied to not
 * use the leftover characters from the old head. Then
 * it frees all the other nodes except the head with
 * ft_free_nodes. */

static void	ft_excess(t_fragment *p_head, t_fragment *last, char *line, int i)
{
	ssize_t	j;

	j = 0;
	while (j < last->sz)
	{
		line[i] = last->fragment[j];
		if (line[i] == '\n')
		{
			i++;
			j++;
			break ;
		}
		i++;
		j++;
	}
	line[i] = '\0';
	i = 0;
	while (j < last->sz)
		p_head->fragment[i++] = last->fragment[j++];
	p_head->sz = i;
	//ft_free_nodes(p_head);
}

/* ft_deduce_line:
 * Calculates the length of the returning str
 * using ft_calculate_length. If the length
 * is 0, it frees the malloced line and the nodes
 * leaving the head intact. If length isnt 0,
 * it copies all the fragments that dont have
 * a \n to the malloced line. Then it handles
 * the last fragment that has a \n and its excess
 * with ft_excess. */

char	*ft_defragment(t_fragment *p_head)
{
	ssize_t		i;
	ssize_t		j;
	size_t		length;
	char		*line;
	t_fragment	*node;

	length = ft_calc_len(p_head);
	line = gc_malloc((length + 1) * sizeof(char));
	if (!line)
		return (/*ft_free_nodes(p_head), */NULL);
	if (length == 0)
		return (/*free(line), ft_free_nodes(p_head), */NULL);
	i = 0;
	node = p_head;
	while (node->stop == 0)
	{
		j = 0;
		while (j < node->sz)
			line[i++] = node->fragment[j++];
		node = node->next;
	}
	return (ft_excess(p_head, node, line, i), line);
}
