/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:32:23 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 03:36:01 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_BONUS_H
# define RAYCASTING_BONUS_H

#include "cub3d_bonus.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
# include <sys/time.h>
#include <unistd.h>
#include <math.h>


#define W 26
#define A 4
#define S 22
#define D 7
#define F 9
#define ESC 41
#define TAB 43
#define BLOCK_SIZE 64
#define LEFT 80
#define RIGHT 79

#define TILE_SIZE 25

#define WIDTH 1000
#define HEIGHT 1000

#define PI 3.14159265359

typedef struct s_vecd {
	double x;
	double y;
} t_vecd;

typedef struct s_ray {
	t_vecd st_cos;  // Step vector for cos intersections
	t_vecd st_sin;  // Step vector for sin intersections  
	double ln_cos;  // Length of cos ray
	double ln_sin;  // Length of sin ray
} t_ray;

typedef struct s_trace {
	t_ray ray;
	t_ray step;
	t_vecd ref;     // Reference position (player)
	float cos_a;    // cos(angle)
	float sin_a;    // sin(angle)
	float newa;     // Normalized angle for fisheye correction
	double len;     // Final ray length
	int map_x;      // Map position X
	int map_y;      // Map position Y
	int wall_side;  // 0=N, 1=S, 2=W, 3=E
	float tex_offset; // Texture offset [0-1]
} t_trace;

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

typedef struct s_door {
	int x;
	int y;
	bool pressed;
}	t_door;


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
    int is_door;    // 1 si c'est une porte, 0 sinon
} t_ray;

typedef struct s_map
{
	char **map;
	char **full_map;
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
	char  *fl;
	mlx_color ceiling;
	char 	*cl;
}				t_color;

typedef struct s_texture
{
	char *north;
	char *south;
	char *west;
	char *east;
	char *door;          // Nouveau: texture pour les portes
	mlx_image north_img;
	mlx_image south_img;
	mlx_image west_img;
	mlx_image east_img;
	mlx_image door_img;  // Nouveau: image pour les portes
	int width;
	int height;
}			t_texture;

typedef struct s_mouse
{
	int x;
	int y;
	int is_press;
}			t_mouse;


// Minimap structure

typedef struct s_minimap
{
	int		skipped;
	int valid;
	char **map;
	mlx_image wall;
	mlx_image back;
	mlx_image character;
	mlx_color *c;
	bool down;
}			t_minimap;

typedef struct s_crowbar
{
	int					valid[4];
	int					x[4];
	int					y[4];
	int 				type;
	mlx_color			*c[4];
	uint64_t			size[4];
	mlx_image			item[4];
	unsigned long long	time[2];
	unsigned long long	wait[2];
	bool 				wheel;
}	t_crowbar;

typedef struct s_fps
{
	long long last_time;
	long long current_time;
	int frame_count;
	int fps;
	long long fps_timer;
}			t_fps;

typedef struct s_game
{
	void *mlx;
	void *win;
	t_crowbar bar;
	t_minimap mini;
	t_player player;
	bool can_toggle_door;
	t_buffer *lst_buffer;
	t_color	color;
	t_texture	texture;
	t_mouse mouse;
	t_map map;
	mlx_color *frame_buffer;
	t_door *d;
	int zone_cx; // centre de la zone actuelle (x en blocs)
    int zone_cy;
	t_fps fps_data;
}			t_game;

typedef struct s_vec2
{
	uint32_t x;
	uint32_t y;
}	vec2;

void pos_mouse(t_game *game);
void key_press(int keycode, void *params);
void key_release(int keycode, void *params);
void move_player(t_player *player, t_game *game);
void	mouse_wheel(int keycode, void *params);
void update_move_player(float x, float y, t_game *game);
long long	current_time(void);
void update_angle(t_player *player);

void init_player(t_player *player);
void mouse_up(int button, void *params);
void	init_item(t_game *game, char path[50], int type);
void mouse_down(int button, void *params);

/* Raycasting functions */
t_ray cast_ray(t_game *game, float angle);
void render_frame(t_game *game);
int is_door_at_position(t_game *game, int map_x, int map_y);

/* Rendering functions */
void init_frame_buffer(t_game *game);
void render_frame(t_game *game);
void draw_vertical_line_no_stretch(t_game *game, int x, float wall_height, t_ray ray);

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

/* FPS functions */
void init_fps(t_game *game);
void update_fps(t_game *game);
void draw_fps(t_game *game);

/* Sprite functions */
void draw_crow(t_game *game);
void draw_exit_kunai(t_game *game, bool *done);
void draw_transition(t_game *game, bool *done);
void draw_sprinting_kunai(t_game *game, bool is_moving);

// minimap function
void	init_minimap(t_game *game);
void draw_minimap(t_game *game);


#endif 
