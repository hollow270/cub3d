/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:29:22 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/21 18:12:05 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"

# define NO_WALL "./assets/north_wall.xpm"
# define EA_WALL "./assets/east_wall.xpm"
# define SO_WALL "./assets/south_wall.xpm"
# define WE_WALL "./assets/west_wall.xpm"

typedef struct s_assets
{
	char	*north_wall;
	char	*east_wall;
	char	*south_wall;
	char	*west_wall;
	int		f_rgb[3];
	int		c_rgb[3];
}			t_assets;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_map_line
{
	char				*line;
	struct s_map_line	*next;
}						t_map_line;

typedef struct s_parse_data
{
	t_assets	*assets;
	t_color		*c_color;
	t_color		*f_color;
	int			is_valid;
	char		**file_content;
	char		**matrix;
	t_map_line	*map_lines;
	int			map_height;
	int			map_width;
	int			p_x;
	int			p_y;
	int			players;
}				t_parse_data;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}						t_garbage;

int			parse_map_file(char *file_name, t_parse_data *p_data);
t_map_line	*interpret_file_content(t_parse_data *p_data);
int			extract_data(t_parse_data *p_data);
int			test_assets(t_parse_data *p_data);
void		skip_leading_spaces(t_parse_data *p_data);
char		**extract_map(t_parse_data *p_data);
int			is_map(char *s);
int			check_enclosed(t_parse_data *p_data);
int			get_player_pos(t_parse_data *p_data);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
char		**ft_split(const char *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t n);
char		*ft_strdup(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);
int		ft_splitlen(char **split);
void		free_map_lines(t_map_line *head);
void		*gc_malloc(size_t size);
void		gc_free_all(void);

#endif