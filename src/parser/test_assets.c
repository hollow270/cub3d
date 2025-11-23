/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:00:49 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/01 19:14:31 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_xpm_helper(char *path);
int	check_xpm_extension(t_parse_data *p_data);
int	check_color_values(int rgb[3]);
int	open_texture_files(t_parse_data *p_data);

int	test_assets(t_parse_data *p_data)
{
	if (check_xpm_extension(p_data) == 0)
		return (printf("Error\nInvalid texture extension\n"), 0);
	if (open_texture_files(p_data) == 0)
		return (printf("Error\nCan't open texture files\n"), 0);
	return (1);
}

int	check_xpm_extension(t_parse_data *p_data)
{
	if (check_xpm_helper(p_data->assets->north_wall) == 0)
		return (0);
	else if (check_xpm_helper(p_data->assets->east_wall) == 0)
		return (0);
	else if (check_xpm_helper(p_data->assets->south_wall) == 0)
		return (0);
	else if (check_xpm_helper(p_data->assets->west_wall) == 0)
		return (0);
	return (1);
}

int	check_xpm_helper(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (ft_strlen(path + i) == 4)
		{
			if (ft_strcmp(path + i, ".xpm") != 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_color_values(int rgb[3])
{
	int	i;

	i = 0;
	while (rgb[i] && i < 3)
	{
		if (rgb[i] < 0)
			return (0);
		i++;
	}
	return (1);
}

int	open_texture_files(t_parse_data *p_data)
{
	int	fd;

	fd = open(p_data->assets->north_wall, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(p_data->assets->east_wall, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(p_data->assets->south_wall, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(p_data->assets->west_wall, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
