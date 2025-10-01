/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:19:52 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/22 17:24:24 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_map_line	*get_map(int fd);
char		**get_file_content(int fd);
char		*join_file_lines(int fd);
int			has_space_only(char *s);
int			check_assets(void);

int	parse_map_file(char *file_name, t_parse_data *p_data)
{
	int	fd;

	p_data->is_valid = 1;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCan't open/inexistent map file\n"), p_data->is_valid = 0, 0);
	p_data->file_content = get_file_content(fd);
	if (!p_data->file_content)
		return (close(fd), printf("Error\nEmpty map/empty lines in map/incomplete map\n"), 0);
	p_data->map_lines = interpret_file_content(p_data);
	if (extract_data(p_data) == 0)
		return (close(fd), 0);
	if (test_assets(p_data) == 0)
		return (close(fd), 0);
	p_data->matrix = extract_map(p_data);
	if (!p_data->matrix)
		return (close(fd), printf("Error\nCan't extract map, probable malloc failure\n"), 0);
	if (check_enclosed(p_data) == 0)
		return (close(fd), printf("Error\nMap is not enclosed in walls\n"), 0);
	if (get_player_pos(p_data) == 0)
		return (close(fd), printf("Error\nMore than one player in map/Invalid char found in map\n"), 0);
	fill_map_space(p_data);
	return (close(fd), 1);
}

char	**get_file_content(int fd)
{
	char	**file_content;

	file_content = ft_split(join_file_lines(fd), '\n');
	if (!file_content)
		return (NULL);
	return (file_content);
}

char	*join_file_lines(int fd)
{
	char	*ret;
	char	*buffer;
	int		in_map;
	char	*prvs;

	ret = NULL;
	in_map = 0;
	prvs = NULL;
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		if (is_map(buffer) && !has_space_only(buffer) && in_map == 0)
			in_map = 1;
		else if (in_map == 1 && buffer[0] == '\n' && ft_strchr(prvs, '0'))
			return (NULL);
		if(!has_space_only(buffer))
			ret = ft_strjoin(ret, buffer);
		prvs = buffer;
	}
	return (ret);
}

int	has_space_only(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	check_assets(void)
{
	int	fd;

	fd = open(NO_WALL, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	fd = open(EA_WALL, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	fd = open(SO_WALL, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	fd = open(WE_WALL, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}
