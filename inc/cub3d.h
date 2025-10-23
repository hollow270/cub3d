/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:29:22 by yhajbi            #+#    #+#             */
/*   Updated: 2025/09/27 17:42:34 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/X.h>
# include <stdbool.h>
# include "get_next_line.h"
# include "../src/.mlx/mlx.h"

# define NO_WALL "./assets/north_wall.xpm"
# define EA_WALL "./assets/east_wall.xpm"
# define SO_WALL "./assets/south_wall.xpm"
# define WE_WALL "./assets/west_wall.xpm"

typedef enum e_wall_type
{
	VERTICAL,
	HORIZONTAL
}	t_wall_type;

typedef struct s_sprites
{
	void	*north_wall;
	void	*east_wall;
	void	*south_wall;
	void	*west_wall;
}			t_sprites;

typedef struct s_assets
{
	char	*north_wall;
	char	*east_wall;
	char	*south_wall;
	char	*west_wall;
	char	*door;
	int		f_rgb[3];
	int		c_rgb[3];
}			t_assets;

typedef struct s_map_line
{
	char				*line;
	struct s_map_line	*next;
}						t_map_line;

typedef struct s_parse_data
{
	t_assets	*assets;
	int			is_valid;
	char		**file_content;
	char		**matrix;
	t_map_line	*map_lines;
	float		p_x;
	float		p_y;
	double		angle;
	int			height;
	int			width;
	int			has_door;
}				t_parse_data;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_parse_data	p_data;
	t_sprites		*sprites;
}					t_vars;

typedef struct s_pos
{
	double	x;
	double	y;
}			t_pos;

typedef struct s_raycast
{
	double	angle;
	//double	**ray_angles;
	t_pos		*h_p;
	t_pos		*v_p;
	t_pos		*p_p;
	t_pos		*tip_p;
	t_wall_type	wall_type;
	int			is_door;
	int			wall_height;
	double		tip_dist;
}			t_raycast;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	angle;
	int		x_step;
	int		y_step;
}	t_player;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_game
{
	t_vars		*vars;
	t_raycast	*rcd;
	t_raycast	*mrcd;
	t_player	player;
	t_img		img;
	int			win_w;
	int			win_h;
	int			minimap_w;
	int			minimap_h;
	void		*n_img;
	void		*e_img;
	void		*s_img;
	void		*w_img;
	void		*d_img;
	int			*n_data;
	int			*e_data;
	int			*s_data;
	int			*w_data;
	int			*d_data;
	int			*chosen_tx;
	double		*ray_angles;
	bool		mouse_control;
}	t_game;

/*		TESTING			

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_game
{
	t_vars		*vars;
	t_player	player;
	t_img		img;
	int			win_w;
	int			win_h;
}	t_game;

		TESTING			*/

int			parse_map_file(char *file_name, t_parse_data *p_data);
t_map_line	*interpret_file_content(t_parse_data *p_data);
int			extract_data(t_parse_data *p_data);
int			test_assets(t_parse_data *p_data);
void		skip_leading_spaces(t_parse_data *p_data);
char		**extract_map(t_parse_data *p_data);
int			is_map(char *s);
int			check_enclosed(t_parse_data *p_data);
int			get_player_pos(t_parse_data *p_data);
void		fill_map_space(t_parse_data *p_data);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
char		**ft_split(const char *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t n);
char		*ft_strdup(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);
int			ft_splitlen(char **split);
char		*ft_strstr(char *s1, char *s2);
void		free_map_lines(t_map_line *head);
void		*gc_malloc(size_t size);
void		gc_free_all(void);

#endif