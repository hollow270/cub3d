/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:55:51 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/18 13:28:28 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* check_head:
 * takes a node and checks if it has a newline
 * setting its int stop member to 1 if it does
 * and to 0 if it doesnt */

static void	ft_check_node(t_fragment *p_head)
{
	int			i;

	i = 0;
	while (i < p_head->sz)
	{
		if (p_head->fragment[i] == '\n')
		{
			p_head->stop = 1;
			return ;
		}
		i++;
	}
	p_head->stop = 0;
}

/* ft_link_check
 * Appends one node to the linked list
 * then checks if it has a newline
 * or is EOF to set the nodes's 
 * int stop member to 1. Or to 0 if it
 * doesnt have EOF or a newline */

static void	ft_link_node(t_fragment *p_head, t_fragment *new)
{
	ssize_t		i;
	t_fragment	*last;

	last = p_head;
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
	i = 0;
	while (i < new->sz)
	{
		if (new->fragment[i] == '\n')
		{
			new->stop = 1;
			break ;
		}
		i++;
	}
	if (i == new->sz)
	{
		if (new->sz < BUFFER_SIZE)
			new->stop = 1;
		else
			new->stop = 0;
	}
}

/* ft_free_nodes:
 * frees all the nodes in a linked list
 * except for its head */

void	ft_free_nodes(t_fragment *p_head)
{
	t_fragment	*node;
	t_fragment	*cup;

	node = p_head->next;
	while (node)
	{
		cup = node->next;
		free(node);
		node = cup;
	}
}

/* ft_get_line:
 * Checks if the head has a \n with check_head
 * then loops to malloc a node to read into 
 * and add it to the end of p_head's list,
 * using ft_link_check , as long as each time
 * the newly malloced node doesnt have a \n
 * when read into. Then calls ft_deduce_line
 * to join the fragments and returns. */

static char	*ft_get_line(t_fragment *p_head, int fd)
{
	t_fragment	*node;

	ft_check_node(p_head);
	node = p_head;
	while (!(node->stop))
	{
		node = gc_malloc(sizeof(t_fragment));
		if (!node)
			return (/*ft_free_nodes(p_head), */NULL);
		node->sz = read(fd, node->fragment, BUFFER_SIZE);
		if (node->sz == -1)
		{
			p_head->sz = 0;
			return (/*free(node), ft_free_nodes(p_head), */NULL);
		}
		ft_link_node(p_head, node);
	}
	return (ft_defragment(p_head));
}

/* get_next_line:
 * protects against invalid fds and BUFFER_SIZE
 * then calls the other functions to do the job. */

char	*get_next_line(int fd)
{
	static t_fragment	head[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024 || read(fd, NULL, 0) == -1)
	{
		head[fd].sz = 0;
		return (NULL);
	}
	head[fd].next = NULL;
	return (ft_get_line(&head[fd], fd));
}
