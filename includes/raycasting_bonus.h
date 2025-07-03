/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:32:23 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 13:58:54 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_BONUS_H
# define RAYCASTING_BONUS_H

# include "cub3d_bonus.h"
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

# define WIDTH 1920
# define HEIGHT 1080

# define PI 3.14159265359

typedef struct s_render_params
{
	float	fov_half;
	float	tan_fov_half;
	float	wall_scale;
}	t_render_params;

typedef struct s_vecd
{
	double	x;
	double	y;
}	t_vecd;

typedef struct s_ray
{
	t_vecd	st_cos;
	float	x;
	float	y;
	float	cos_angle;
	float	sin_angle;
	float	dist;
	int		is_vertical;
	int		wall_side;
	float	wall_x;
	int		is_door;
	t_vecd	st_sin;
	double	ln_cos;
	double	ln_sin;
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

typedef struct s_door
{
	int		x;
	int		y;
	bool	pressed;
}	t_door;

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
	char		*door;
	mlx_image	north_img;
	mlx_image	south_img;
	mlx_image	west_img;
	mlx_image	east_img;
	mlx_image	door_img;
	int			width;
	int			height;
}	t_texture;

typedef struct s_mouse
{
	int	x;
	int	y;
	int	is_press;
}	t_mouse;

typedef struct s_minimap
{
	int			skipped;
	int			valid;
	char		**map;
	mlx_image	wall;
	mlx_image	back;
	mlx_image	character;
	mlx_color	*c;
	bool		down;
}	t_minimap;

typedef struct s_crowbar
{
	int					valid[4];
	int					x[4];
	int					y[4];
	int					type;
	mlx_color			*c[4];
	uint64_t			size[4];
	mlx_image			item[4];
	unsigned long long	time[2];
	unsigned long long	wait[2];
	bool				wheel;
}	t_crowbar;

typedef struct s_fps
{
	long long	last_time;
	long long	current_time;
	int			frame_count;
	int			fps;
	long long	fps_timer;
}	t_fps;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_crowbar	bar;
	t_minimap	mini;
	t_player	player;
	bool		can_toggle_door;
	t_buffer	*lst_buffer;
	t_color		color;
	t_texture	texture;
	t_mouse		mouse;
	t_map		map;
	mlx_color	*frame_buffer;
	t_door		*d;
	int			zone_cx;
	int			zone_cy;
	t_fps		fps_data;
}			t_game;

typedef struct s_render_vars
{
	t_game			*game;
	t_ray			ray;
	mlx_image		*texture;
	mlx_color		*column;
	int				start_y;
	int				end_y;
	int				tex_x;
	float			tex_pos;
	float			step;
}	t_render_vars;

typedef struct s_vec2
{
	uint32_t	x;
	uint32_t	y;
}	t_vec2;

typedef struct s_minimap_config
{
	t_vec2	map_size;
	t_vec2	minimap_size;
	t_vec2	offset;
}	t_minimap_config;

void				pos_mouse(t_game *game);
void				key_press(int keycode, void *params);
void				key_release(int keycode, void *params);
int					len_max(char **str);
void				move_player(t_player *player, t_game *game);
void				mouse_wheel(int keycode, void *params);
void				update_move_player(float x, float y, t_game *game);
long long			current_time(void);
void				update_angle(t_player *player);

void				init_player(t_player *player);
int					init_mlx(t_game *game);
void				mouse_up(int button, void *params);
void				init_item(t_game *game, char path[50], int type);
void				mouse_down(int button, void *params);

/* Raycasting functions */
t_ray				cast_ray(t_game *game, float angle);
void				render_frame_ttranche(t_game *game);
void				init_render_vars(t_render_vars *vars, int x,
						float wall_height);
void				init_item(t_game *game, char path[50], int type);
void				init_pixel(t_game *game);
void				set_wait_time(t_game *game, int type);
t_minimap_config	get_minimap_config(t_game *game);
int					get_max_steps(t_game *game);
t_trace				init_trace(t_game *game, float angle, float relative_angle);
void				get_collide_pos(t_trace *tr);
int					is_door_at_position(t_game *game, int map_x, int map_y);
void				render_frameranche(t_game *game);
void				process_column(t_game *game, int x, t_render_params params);
void				make_sprite(t_game *game);
void				handle_max_steps_reached(t_trace *tr, int max_steps);
t_ray				create_result(t_game *game, t_trace *tr);
void				handle_wall_hit(t_trace *tr);
t_ray				cast_ray_corrected(t_game *game, float angle,
						float relative_angle);
t_ray				cast_ray(t_game *game, float angle);
t_ray				get_init_ray(float cos_a, float sin_a, double x, double y);
void				cast_forward(t_ray *ray, t_ray *step);
float				calc_tex_offset(t_trace *tr);
int					check_wall(t_game *game, int x, int y);
void				allocate_item_memory(t_game *game, int type);
bool				check_window_size(t_game *game, int type);
void				fill_item(t_game *game, char path[50], int type);
void				set_item_dimensions(t_game *game);
void				handle_file_error(t_game *game, int type);
void				render_ceiling_and_floor(t_render_vars *vars);
void				setup_texture_mapping(t_render_vars *vars,
						float wall_height);
void				render_wall_column(t_render_vars *vars);
int					is_door_at_position(t_game *game, int map_x, int map_y);

/* Rendering functions */
void				init_frame_buffer(t_game *game);
void				render_frame(t_game *game);
void				draw_vertical_line_no_stretch(t_game *game, int x,
						float wall_height, t_ray ray);
void				put_region_to_array(mlx_color *fb, t_vec2 start,
						t_vec2 size, mlx_color *src);

/* Game functions */
void				init_game(t_game *game);
void				close_win(int event, void *params);
void				init_player_position(t_game *game, int x, int y);
void				set_player_angle(t_game *game, char dir);
void				load_map_data(t_game *game);
void				check_all(int keycode, t_game *game);
int					nearest_door(t_game *game);
int					load_textures(t_game *game);
void				draw_loop(void *params);
void				load_map_data(t_game *game);
bool				touch(t_game *game, float x, float y);
int					get_max_map_width(char **map);
void				cleanup_game(t_game *game);
int					load_textures(t_game *game);

/* FPS functions */
void				init_fps(t_game *game);
void				update_fps(t_game *game);
void				draw_fps(t_game *game);

/* Sprite functions */
void				draw_crow(t_game *game);
void				draw_exit_kunai(t_game *game, bool *done);
void				draw_transition(t_game *game, bool *done);
void				draw_sprinting_kunai(t_game *game, bool is_moving);

// minimap function
void				init_minimap(t_game *game);
void				draw_minimap(t_game *game);

#endif 