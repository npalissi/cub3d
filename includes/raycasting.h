/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:32:23 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 11:01:00 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <math.h>

# define W 26
# define A 4
# define S 22
# define D 7
# define F 9
# define ESC 41
# define TAB 43
# define BLOCK_SIZE 64
# define LEFT 80
# define RIGHT 79

# define TILE_SIZE 25

# define WIDTH 1000
# define HEIGHT 1000

# define PI 3.14159265359

typedef struct s_vecd
{
	double	x;
	double	y;
}	t_vecd;

typedef struct s_ray
{
	t_vecd	st_cos;
	t_vecd	st_sin;
	double	ln_cos;
	double	ln_sin;
	float	x;
	float	y;
	float	cos_angle;
	float	sin_angle;
	float	dist;
	int		is_vertical;
	int		wall_side;
	float	wall_x;
	int		is_door;
}	t_ray;

typedef struct s_trace
{
	t_ray		ray;
	t_ray		step;
	t_vecd		ref;
	float		cos_a;
	float		sin_a;
	float		newa;
	double		len;
	int			map_x;
	int			map_y;
	int			wall_side;
	float		tex_offset;
}	t_trace;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir;
	float	angle;
	float	cos_angle;
	float	sin_angle;
	bool	left_rotate;
	bool	right_rotate;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
}	t_player;

typedef struct s_map
{
	char	**map;
	char	**full_map;
	char	*str;
	int		w;
	int		h;
}	t_map;

typedef struct s_buffer
{
	char			buffer[5];
	struct s_buffer	*next;
}	t_buffer;

typedef struct s_color
{
	mlx_color	floor;
	char		*fl;
	mlx_color	ceiling;
	char		*cl;
}	t_color;

typedef struct s_texture
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	mlx_image	north_img;
	mlx_image	south_img;
	mlx_image	west_img;
	mlx_image	east_img;
	int			width;
	int			height;
}	t_texture;

typedef struct s_render_params
{
	float	fov_half;
	float	tan_fov_half;
	float	wall_scale;
}	t_render_params;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			skipped;
	t_player	player;
	bool		can_toggle_door;
	t_buffer	*lst_buffer;
	t_color		color;
	t_texture	texture;
	t_map		map;
	mlx_color	*frame_buffer;
	int			zone_cx;
	int			zone_cy;
}	t_game;

typedef struct s_render_vars
{
	t_game		*game;
	t_ray		ray;
	mlx_image	*texture;
	mlx_color	*column;
	int			start_y;
	int			end_y;
	int			tex_x;
	float		tex_pos;
	float		step;
}				t_render_vars;

void		pos_mouse(t_game *game);
void		key_press(int keycode, void *params);
void		key_release(int keycode, void *params);
void		move_player(t_player *player, t_game *game);
void		update_move_player(float x, float y, t_game *game);
void		update_angle(t_player *player);

void		init_player(t_player *player);
void		mouse_up(int button, void *params);
void		init_item(t_game *game, char path[50], int type);
void		mouse_down(int button, void *params);

/* Raycasting functions */
t_ray		cast_ray(t_game *game, float angle);
t_ray		cast_ray_corrected(t_game *game, float angle, float relative_angle);
void		render_frame(t_game *game);

/* Raycast utils functions */
double		calc_sqrtlen(t_vecd v);
int			check_wall(t_game *game, int x, int y);
int			get_max_steps(t_game *game);
void		cast_forward(t_ray *ray, t_ray *step);
void		get_collide_pos(t_trace *tr);

/* Ray calculation functions */
t_ray		get_init_ray(float cos_a, float sin_a, double x, double y);
float		calc_tex_offset(t_trace *tr);
t_trace		init_trace(t_game *game, float angle, float relative_angle);
void		handle_wall_hit(t_trace *tr);
void		handle_max_steps_reached(t_trace *tr, int max_steps);

/* Ray rendering functions */
t_ray		create_result(t_game *game, t_trace *tr);
void		process_column(t_game *game, int x, t_render_params params);

/* Rendering functions */
void		init_frame_buffer(t_game *game);
void		draw_vertical_line_no_stretch(t_game *game, int x,
				float wall_height, t_ray ray);

/* Render utils functions */
void		init_render_vars(t_render_vars *vars, int x, float wall_height);
void		render_ceiling_and_floor(t_render_vars *vars);
void		setup_texture_mapping(t_render_vars *vars, float wall_height);
void		render_wall_column(t_render_vars *vars);

/* Parsing utils functions */
int			len_max(char **str);
int			find_y(char **map, int i);
int			find_x(char **map, int i);
int			find_char(char *str, char c);
char		*concat_map(char **map);
int			count_occurrences(char *key, char **m);
void		fill_map(char **map, int i);

/* Game functions */
void		init_game(t_game *game);
void		close_win(int event, void *params);
void		draw_loop(void *params);
void		load_map_data(t_game *game);
void		cleanup_game(t_game *game);
int			load_textures(t_game *game);
int			init_mlx(t_game *game);
void		setup_hooks(t_game *game);

#endif 
