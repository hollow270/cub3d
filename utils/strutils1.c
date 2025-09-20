/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:13:24 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/20 14:14:21 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*ft_strdup(const char *s)
{
	char	*d_s;
	char	*d;

	d_s = (char *)gc_malloc(ft_strlen(s) + 1);
	if (!d_s)
		return (NULL);
	d = d_s;
	while (*s)
	{
		*d_s = *s;
		d_s++;
		s++;
	}
	*d_s = '\0';
	return (d);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2 && n != 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_check(const char *start, int sz, int sign)
{
	while (*start == 48)
	{
		start++;
		sz--;
	}
	if (sz > 19)
		return (0);
	if (sz < 19)
		return (1);
	if (ft_strncmp(start, "9223372036854775807", sz) > 0 && sign)
		return (0);
	if (ft_strncmp(start, "9223372036854775808", sz) > 0 && sign == -1)
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	long long	num;
	int			sign;
	const char	*start;

	num = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr++ == '-')
			sign = -1;
	}
	start = nptr;
	while (*nptr >= '0' && *nptr <= '9')
		num = num * 10 + (*nptr++ - '0');
	if (!ft_check(start, nptr - start, sign))
	{
		if (sign == 1)
			return (-1);
		if (sign == -1)
			return (0);
	}
	return ((int)(sign * num));
}
