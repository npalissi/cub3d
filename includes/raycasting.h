/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:32:23 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/24 18:25:02 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

#include "cub3d.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


#define W 26
#define A 4
#define S 22
#define D 7
#define ESC 41
#define TAB 43
#define BLOCK_SIZE 64
#define LEFT 80
#define RIGHT 79

#define TILE_SIZE 25

#define WIDTH 1000
#define HEIGHT 1000

#define PI 3.14159265359



typedef struct s_player
{
	float x;
	float y;
	float dir;
	float angle;
	float cos_angle;
	float sin_angle;
	
	bool left_rotate;
	bool right_rotate;
	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;
}				t_player;

typedef struct s_ray
{
    float x;
    float y;
    float cos_angle;
    float sin_angle;
    float dist;
    int is_vertical;
    int wall_side;  // 0=North, 1=South, 2=West, 3=East
    float wall_x;   // Position x sur le mur pour la texture
} t_ray;

typedef struct s_map
{
	char **map;
	char *str;
	int w;
	int h;
}				t_map;

typedef struct	s_buffer
{
	char			buffer[5];
	struct s_buffer	*next;

}				t_buffer;

typedef struct s_color
{
	mlx_color floor;
	mlx_color ceiling;
}				t_color;

typedef struct s_texture
{
	char *north;
	char *south;
	char *west;
	char *east;
	mlx_image north_img;
	mlx_image south_img;
	mlx_image west_img;
	mlx_image east_img;
	int width;
	int height;
}			t_texture;

typedef struct s_mouse
{
	int x;
	int y;
	int is_press;
}			t_mouse;


typedef struct s_render_data
{
	float	fov_half;
	float	angle_step;
	float	projection_dist;
	float	ray_angle;
	t_ray	ray;
	float	wall_height;
}			t_render_data;

typedef struct s_minimap
{
	int valid;
	char **map;
	mlx_image wall;
	mlx_color *w;
	mlx_image back;
	mlx_color *b;
	mlx_image character;
	mlx_color *c;
	bool down;
}			t_minimap;

typedef struct s_game
{
	void *mlx;
	void *win;
	void *img;
	t_minimap mini;
	t_player player;
	t_buffer *lst_buffer;
	t_color	color;
	t_texture	texture;
	t_mouse mouse;
	t_map map;
	mlx_color *frame_buffer;
	int zone_cx; // centre de la zone actuelle (x en blocs)
    int zone_cy;
}			t_game;

void pos_mouse(t_game *game);
void key_press(int keycode, void *params);
void key_release(int keycode, void *params);
void move_player(t_player *player, t_game *game);
void update_move_player(float x, float y, t_game *game);
void update_angle(t_player *player);

void init_player(t_player *player);
void mouse_up(int button, void *params);
void mouse_down(int button, void *params);

/* Raycasting functions */
t_ray cast_ray(t_game *game, float angle);
float get_ray_pos_y(t_game *game, float angle);
float get_ray_pos_x(t_game *game, float angle);
float calculate_distance(t_game *game, float ray_x, float ray_y);
int is_wall_hit(t_game *game, float ray_x, float ray_y);

/* Rendering functions */
void init_frame_buffer(t_game *game);
void render_frame(t_game *game);
void draw_vertical_line(t_game *game, int x, float wall_height, t_ray ray);

/* Lighting functions */
mlx_color calculate_wall_color(mlx_color base_color);
mlx_color get_ceiling_color(void);
mlx_color get_floor_color(void);

/* Game functions */
void init_game(t_game *game);
void close_win(int event, void *params);
void draw_loop(void *params);
void load_map_data(t_game *game);
bool touch(t_game *game, float x, float y);
void cleanup_game(t_game *game);
int load_textures(t_game *game);

// minimap function
void	init_minimap(t_game *game);
void draw_minimap(t_game *game);


#endif 