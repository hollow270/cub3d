/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:29:22 by yhajbi            #+#    #+#             */
/*   Updated: 2025/12/03 17:12:52 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../.mlx/mlx.h"
# include "get_next_line.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define WIDTH 1920
# define HEIGHT 1000

# define MOVE_SPEED 0.11
# define ROT_SPEED 0.05
# define MOUSE_ROT_SPEED 0.00035

# define NO_WALL "./assets/north_wall.xpm"
# define EA_WALL "./assets/east_wall.xpm"
# define SO_WALL "./assets/south_wall.xpm"
# define WE_WALL "./assets/west_wall.xpm"
# define HELL_YEAH "./assets/budweiser.xpm"

#define MM_RADIUS_PX      75
#define MM_PIX_PER_CELL    8
#define MM_MARGIN_X       12
#define MM_MARGIN_Y       12

#define HAND_HEIGHT_PX      900    // change this to resize the hand
#define HAND_BOB_PIX        14     // vertical bob amplitude
#define HAND_CROP_TOP_PCT   40     // % of source trimmed from top (0..99)

// # define PI 3.14159
// # define FOV 60
// # define CUBE_SIZE 64
// # define MINIMAP_SIZE 10
// # define RAY_WIDTH 3
// # define PLAYER_SIZE 10
// # define ROT_SPEED 8
// # define MOVE_SPEED 0.06
// # define WHITE 0xFFFFFF
// # define GROUND 0x2b2b2a
// # define SKY 0x87CEEB
// # define BLACK 0x000000
// # define BROWN 0x964B00
// # define PLAYER_COLOR 0xFF0000
// # define COLLIDER_SZ 0.4
// # define PX_SIZE 3
// # define DOOR_OPEN_DIST 140
// # define DOOR_MIN_ODIST 35
// # define WIN_W 1000
// # define WIN_H 1000

# ifndef TEX_WALL_COUNT
#  define TEX_WALL_COUNT 4
#  define TEX_N 0
#  define TEX_S 1
#  define TEX_W 2
#  define TEX_E 3
# endif

typedef enum e_wall_type
{
	VERTICAL,
	HORIZONTAL
}						t_wall_type;

typedef struct s_sprites
{
	void				*north_wall;
	void				*east_wall;
	void				*south_wall;
	void				*west_wall;
}						t_sprites;

typedef struct s_assets
{
	char				*north_wall;
	char				*east_wall;
	char				*south_wall;
	char				*west_wall;
	char				*hell_yeah;
	char				*door;
	int					f_rgb[3];
	int					c_rgb[3];
	int					f_color;
	int					c_color;
}						t_assets;

typedef struct s_map_line
{
	char				*line;
	struct s_map_line	*next;
}						t_map_line;

typedef struct s_img
{
	void				*img;
	char				*data_img;
	int					bpp;
	int					line_len;
	int					endian;
}						t_img;

typedef struct s_player
{
	double				x;
	double				y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
}						t_player;

typedef struct s_keys
{
	int					up;
	int					down;
	int					right;
	int					left;
	int					rot_r;
	int					rot_l;
	int					use;
}						t_keys;

typedef struct s_tex
{
	void				*img;
	char				*data;
	int					w;
	int					h;
	int					bpp;
	int					line_len;
	int					endian;
}						t_tex;

typedef struct s_game
{
        void            *mlx;
        void            *win;
        t_img           frame;
        t_player        player;
        t_keys          keys;
        int                     map_w;
        int                     map_h;
        char            **map;
        char            *filename;
        int                     ceiling;
        int                     floor;
        char            *tex_path[TEX_WALL_COUNT];
        t_tex           wall[TEX_WALL_COUNT];
        char            *door_path;
        t_tex           door;
        char            *hand_path;
        t_tex           hand;
        double          hand_phase;
}       t_game;

typedef struct s_parse_data
{
	t_assets			*assets;
	int					is_valid;
	char				**file_content;
	char				**matrix;
	t_map_line			*map_lines;
	float				p_x;
	float				p_y;
	double				angle;
	int					height;
	int					width;
	int					has_door;
}						t_parse_data;

typedef struct s_vars
{
	void				*mlx;
	void				*win;
	t_parse_data		p_data;
	t_sprites			*sprites;
}						t_vars;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}						t_garbage;


//	RENDERER
int	main_function(t_game *gm);
void	start_game(t_game *gm);
int             parse_config(t_game *gm, const char *filename);
void    render_image(t_game *gm);
bool    is_wall(t_game *gm, int x, int y);
void    put_pixel(t_game *gm, int x, int y, int color);
int             close_win(t_game *g);
int             mouse_move(int x, int y, t_game *g);
void    rotate_player(t_player *p, double angle);
int             key_press(int keycode, t_game *g);
int             key_release(int keycode, t_game *g);
void    move_player(t_game *gm);
bool    is_solid_for_ray(t_game *gm, int x, int y);

void    free_map(char **map);
int             load_textures(t_game *gm);
void    free_textures(t_game *gm);
void    draw_minimap(struct s_game *gm);
unsigned int texel_at(t_tex *t, int x, int y);
void    toggle_door(t_game *gm);
void    draw_hands(t_game *gm);
bool    inside_portal(t_game *gm, int map_x, int map_y, double side_distx, double side_disty, double ray_dir_x, double ray_dir_y, int x, int y);


// PARSER

void					ifc_helper1(t_parse_data *p_data,
							t_map_line **map_lines, int *txtr_found, int i);
void					ifc_helper2(t_parse_data *p_data,
							t_map_line **map_lines, int *limit, int *i);
void					ifc_helper3(t_parse_data *p_data,
							t_map_line **map_lines, int i);
t_map_line				*create_line_node(char *line);
void					add_line_node(t_map_line **map_lines, t_map_line *new);
int						parse_map_file(char *file_name, t_parse_data *p_data);
t_map_line				*interpret_file_content(t_parse_data *p_data);
int						extract_data(t_parse_data *p_data);
int						test_assets(t_parse_data *p_data);
void					skip_leading_spaces(t_parse_data *p_data);
char					**extract_map(t_parse_data *p_data);
int						is_map(char *s);
int						check_enclosed(t_parse_data *p_data);
int						get_player_pos(t_parse_data *p_data);
void					fill_map_space(t_parse_data *p_data);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strchr(const char *s, int c);
char					**ft_split(const char *s, char c);
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlen(const char *s);
size_t					ft_strlcpy(char *dest, const char *src, size_t n);
char					*ft_strdup(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *nptr);
int						ft_splitlen(char **split);
char					*ft_strstr(char *s1, char *s2);
int						ft_charcount(char *s, int c);
void					free_map_lines(t_map_line *head);
void					*gc_malloc(size_t size);
void					gc_free_all(void);
int						check_duplicates(t_parse_data p_data);
int						check_outofbounds_floor(char **map, int x, int y);
int						check_color_data(t_assets *a);
void					merge_data(t_parse_data p_data, t_game *g);

#endif
