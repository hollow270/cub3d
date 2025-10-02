/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:26:18 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/18 11:28:39 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_garbage	**get_gc_head(void)
{
	static t_garbage	*head = NULL;

	return (&head);
}

void    *gc_malloc(size_t size)
{
	t_garbage	**head;
	void		*ptr;
	t_garbage	*node;

	head = get_gc_head();
	ptr = malloc(size);
	if (!ptr)
			return (NULL);
	node = malloc(sizeof(t_garbage));
	if (!node)
	{
			free(ptr);
			return (NULL);
	}
	node->ptr = ptr;
	node->next = *head;
	*head = node;
	return (ptr);
}

void    gc_free_all(void)
{
	t_garbage	**head;
	t_garbage	*current;
	t_garbage	*next;

	head = get_gc_head();
	current = *head;
	while (current)
	{
			next = current->next;
			free(current->ptr);
			free(current);
			current = next;
	}
	*head = NULL;
}
