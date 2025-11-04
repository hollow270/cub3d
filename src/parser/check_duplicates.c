/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:02:15 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/04 20:45:43 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	has_only(char *s, int c);

int check_duplicates(t_parse_data p_data)
{
	char	**content;
	int		i;
	int		j;
	int		count;

	content = p_data.file_content;
	i = 0;
	while (content[i])
	{
		j = 0;
		count = 0;
		/* printf("started\n"); */
		if (has_only(content[i], '1'))
			return (1);
		/* printf("%s\n", content[i]); */
		while (content[j])
		{
			/* printf("%s\n", content[j]); */
			if (ft_strcmp(content[i], content[j]) == 0 && count == 0)
				count++;
			else if (ft_strcmp(content[i], content[j]) == 0 && count > 0)
			{
				printf("%s | %s\n", content[i], content[j]);
				return (0);
			}
			/* printf("reached\n"); */
			j++;
		}
		i++;
	}
	return (1);
}

int	has_only(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			return (0);
		i++;
	}
	return (1);
}

