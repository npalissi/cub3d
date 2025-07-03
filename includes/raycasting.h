/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:32:23 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/02 23:29:21 by edubois-         ###   ########.fr       */
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

typedef struct s_ray_tt
{
	t_vecd	st_cos;
	t_vecd	st_sin;
	double	ln_cos;
	double	ln_sin;
}	t_ray_tt;

typedef struct s_trace_tt
{
	t_ray_tt	ray;
	t_ray_tt	step;
	t_vecd		ref;
	float		cos_a;
	float		sin_a;
	float		newa;
	double		len;
	int			map_x;
	int			map_y;
	int			wall_side;
	float		tex_offset;
}	t_trace_tt;

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

typedef struct s_ray
{
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

typedef struct s_minimap
{
	int	skipped;
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
	t_minimap	mini;
	t_player	player;
	t_buffer	*lst_buffer;
	t_color		color;
	t_texture	texture;
	t_map		map;
	mlx_color	*frame_buffer;
	int			zone_cx;
	int			zone_cy;
}			t_game;

void		pos_mouse(t_game *game);
void		key_press(int keycode, void *params);
void		key_release(int keycode, void *params);
void		move_player(t_player *player, t_game *game);
void		mouse_wheel(int keycode, void *params);
void		update_move_player(float x, float y, t_game *game);
long long	current_time(void);
void		update_angle(t_player *player);
void		init_player(t_player *player);
void		mouse_up(int button, void *params);
void		mouse_down(int button, void *params);
void		init_item(t_game *game, char path[50], int type);

/* Raycasting functions */
t_ray		cast_ray(t_game *game, float angle);
void		render_frame_ttranche(t_game *game);
int			is_door_at_position(t_game *game, int map_x, int map_y);

/* Rendering functions */
void		init_frame_buffer(t_game *game);
void		render_frame(t_game *game);
void		draw_vertical_line_no_stretch(t_game *game, int x,
				float wall_height, t_ray ray);

/* Lighting functions */
mlx_color	calculate_wall_color(mlx_color base_color);
mlx_color	get_ceiling_color(void);
mlx_color	get_floor_color(void);

/* Game functions */
void		init_game(t_game *game);
void		close_win(int event, void *params);
void		draw_loop(void *params);
void		load_map_data(t_game *game);
bool		touch(t_game *game, float x, float y);
void		cleanup_game(t_game *game);
int			load_textures(t_game *game);

/* FPS functions */
void		init_fps(t_game *game);
void		update_fps(t_game *game);
void		draw_fps(t_game *game);

/* Sprite functions */
void		draw_crow(t_game *game);
void		draw_exit_kunai(t_game *game, bool *done);
void		draw_transition(t_game *game, bool *done);
void		draw_sprinting_kunai(t_game *game, bool is_moving);

// minimap function
void		init_minimap(t_game *game);
void		draw_minimap(t_game *game);

#endif 