/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:29:22 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/04 20:29:53 by yhajbi           ###   ########.fr       */
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

# define PI 				3.14159
# define FOV				60
# define CUBE_SIZE		64
# define MINIMAP_SIZE	10
# define RAY_WIDTH		3
# define PLAYER_SIZE		10
# define ROT_SPEED		10
# define MOVE_SPEED		0.1
# define WHITE			0xFFFFFF
# define GROUND			0x2b2b2a
# define SKY				0x87CEEB
# define BLACK			0x000000
# define BROWN			0x964B00
# define PLAYER_COLOR	0xFF0000
# define PX_SIZE			5
# define DOOR_OPEN_DIST	140
# define WIN_W			1000
# define WIN_H			1000

typedef struct s_minimap
{
	int		map_x;
	int		map_y;
	int		pixel_x;
	int		pixel_y;
	int		cube_x;
	int		cube_y;
	int		start_cube_x;
	int		start_cube_y;
	char	**map;
}			t_minimap;

typedef struct s_player_mp
{
	char	**map;
	int		start_player_x;
	int		start_player_y;
	int		player_x;
	int		player_y;
	int		pixel_x;
	int		pixel_y;
}			t_player_mp;

typedef struct s_wall_ctx
{
	double	progress;
	int		x;
	int		y;
	int		tx_x;
	int		tx_y;
}			t_wall_ctx;

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
	char	*hell_yeah;
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
	double		angle;
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
	double	bob_time;
	double	bob_amplitude;
	double	bob_frequency;
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
	void		*h_img;
	int			*n_data;
	int			*e_data;
	int			*s_data;
	int			*w_data;
	int			*d_data;
	int			*h_data;
	int			*chosen_tx;
	double		*ray_angles;
	bool		mouse_control;
}	t_game;

// PARSER

void		ifc_helper1(t_parse_data *p_data,
				t_map_line **map_lines, int *txtr_found, int i);
void		ifc_helper2(t_parse_data *p_data,
				t_map_line **map_lines, int *limit, int *i);
void		ifc_helper3(t_parse_data *p_data,
				t_map_line **map_lines, int i);
t_map_line	*create_line_node(char *line);
void		add_line_node(t_map_line **map_lines, t_map_line *new);
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
int			check_duplicates(t_parse_data p_data);

// RENDERER

int			render(t_game *g);
void		init_raycast_data(t_game *g);
void		init_raycast_data2(t_game *g);
void		render_map(t_game *g);
void		render_map_background(t_game *g);
void		render_player(t_game *g);
void		render_vision_ray(t_game *g);
void		render_hell_yeah_pov(t_game *g);
void		save_middle_ray(t_game *g, double **ray_angles);
void		cast_rays(t_game *g, double ray_angle, int j);
void		get_horizontal_intercept(t_game *g, t_raycast *rcd,
				double angle, int flag);
void		get_vertical_intercept(t_game *g, t_raycast *rcd,
				double angle, int flag);
void		choose_ray_tip(t_game *g);
void		choose_texture(t_game *g, double ray_angle);
void		init_ray_angles(t_game *g, double *ray_angles);
void		choose_ray_tip2(t_game *g);
void		calc_wall_dist2(t_game *g, double ray_angle);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		calc_wall_dist(t_game *g, double ray_angle);
void		ghi_helper(t_raycast *rcd, double angle, double *y_step);
void		gvi_helper(t_raycast *rcd, double angle, double *x_step);
int			is_wall(t_game *g, double x, double y, int flag);
double		calc_dist(t_pos *p1, t_pos *p2);
void		set_tip(t_pos *dst, t_pos *src,
				t_wall_type *wall_type_dst, t_wall_type wall_type);
void		check_door_intercept(t_game *g);
void		draw_stripe(t_game *g, int w_x, int ws_y, int we_y);
void		draw_ceiling(t_game *g, int c_x, int cs_y, int ce_y);
void		draw_ground(t_game *g, int g_x, int gs_y, int ge_y);
void		draw_wall(t_game *g, int w_x, int ws_y, int we_y);
void		draw_pixel_from_sprite(t_game *g,
				t_wall_ctx *wctx, int w_x, int ws_y);
void		draw_mp_square(t_game *g, t_minimap *mp);
int			isnt_wall(int c);
void		draw_mp_pixel(t_game *g, t_minimap *mp);
void		cube_init(t_vars *vars);
void		init_game_data(t_game *g, t_vars *vars);
void		init_sprites(t_game *g);
void		init_data_addresses(t_game *g);
int			controls(int keycode, t_game *g);
int			controls_helper1(int keycode, t_game *g);
void		controls_helper2(int keycode, t_game *g);
int			close_game(t_game *g);
int			pointer_motion(int x, int y, t_game *g);
void		move_forward(t_game *g, double angle);
void		move_backward(t_game *g, double angle);
int			check_new_position(double new_x, double new_y, t_game *g, int dir);
void		use_door(t_game *g);
void		set_door_status(t_game *g, char **map, int x, int y);
int			is_not_passable(int c);
int			isnt_wall(int c);
void		strafe_left(t_game *g, double angle, int dir);
void		strafe_right(t_game *g, double angle, int dir);

#endif
