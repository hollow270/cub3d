/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:37:16 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/11 20:10:50 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*ft_strstr(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		if (ft_strncmp(s1 + i, s2, ft_strlen(s2)) == 0)
			return (s1 + i);
		i++;
	}
	return (NULL);
}

int	ft_charcount(char *s, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}
