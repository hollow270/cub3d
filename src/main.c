/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:28:41 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/28 15:01:33 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		check_extension(char *file_name);

int	main(int argc, char *argv[])
{
	t_vars	vars;
	t_game	g;

	if (argc != 2)
		return (printf("Error\nInvalid arguments\n"), 1);
	if (check_extension(argv[1]) == 0)
		return (printf("Error\nInvalid file extension\n"), 2);
	if (parse_map_file(argv[1], &vars.p_data) == 0 || vars.p_data.is_valid == 0)
		return (gc_free_all(), 3);
	if (check_duplicates(vars.p_data) == 0)
		return (gc_free_all(),
			printf("Error\nDuplicate asset lines in map file\n"), 3);

	merge_data(vars.p_data, &g);
	g.filename = argv[1];

	printf("player pos = [%f, %f]\n", g.player.x, g.player.y);
	printf("map dimensions = [%d, %d]\n", g.map_w, g.map_h);
	int	i = 0;
	while (g.map[i])
		printf("%s\n", g.map[i++]);
	printf("filename = [%s]\n", g.filename);
	printf("ceiling color = [%d]\nfloor color = [%d]\n", g.ceiling, g.floor);
	printf("north texture path = [%s]\n", g.tex_path[TEX_N]);
	printf("east texture path = [%s]\n", g.tex_path[TEX_E]);
	printf("south texture path = [%s]\n", g.tex_path[TEX_S]);
	printf("west texture path = [%s]\n", g.tex_path[TEX_W]);
	printf("door texture path = [%s]\n", g.door_path);

	/*
		* RENDERING
		* STUFF
		* 			*/

	gc_free_all();
	return (0);
}

int	check_extension(char *file_name)
{
	int	i;

	i = 0;
	if (file_name[i] == '.' && ft_strcmp(file_name, ".cub"))
		return (0);
	while (file_name[i] && file_name[i] != '.')
		i++;
	if (!file_name[i])
		return (0);
	if (ft_strcmp(file_name + i, ".cub") != 0)
		return (0);
	return (1);
}
