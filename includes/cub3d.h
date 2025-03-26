/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:43:09 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/26 12:51:36 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include "../MacroLibX/includes/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../lib/libft/libft.h"

#define W 26
#define A 4
#define S 22
#define D 7
#define ESC 41
#define BLOCK_SIZE 64
#define LEFT 80
#define RIGHT 79

#define WIDTH 1000
#define HEIGHT 1000

#define PI 3.14159265359



typedef struct s_player
{
	float x;
	float y;
	float dir;
	float angle;

	bool left_rotate;
	bool right_rotate;
	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;
}				t_player;

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
	unsigned int floor;
	unsigned int ceiling;
}				t_color;


typedef struct s_mat
{
	char *north;
	char *south;
	char *west;
	char *east;	
}			t_mat;

typedef struct s_mouse
{
	int x;
	int y;
	int is_press;
}			t_mouse;


typedef struct s_game
{
	void *mlx;
	void *win;
	void *img;
	char *str_map;
	t_player player;
	t_buffer *lst_buffer;
	t_color	color;
	t_mat	mat;
	t_mouse mouse;
	t_map map;
}			t_game;

void pos_mouse(t_game *game);
char *recover_file(t_game *game, char *name_file);
int init_data(t_game *game);
void draw_squar(t_game *game, int x, int y, int size);
void key_press(int keycode, void *params);
void key_release(int keycode, void *params);
void move_player(t_player *player, t_game *game);

void init_player(t_player *player);
void mouse_up(int button, void *params);
void mouse_down(int button, void *params);

#endif