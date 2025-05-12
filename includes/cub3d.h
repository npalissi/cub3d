/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:43:09 by npalissi          #+#    #+#             */
/*   Updated: 2025/05/12 14:22:59 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define WALL '1'
#define EMPTY '0'
#define VISITED 'F'


#include "../MacroLibX/includes/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "../lib/libft/libft.h"
#include "../lib/printf_fd/ft_printf.h"
#include "../lib/gnl/get_next_line.h"

#include "../lib/MacroLibX/includes/mlx.h"
#include "../lib/MacroLibX/includes/mlx_extended.h"

typedef struct s_map
{
	char **map;
	char *str;
	int w;
	int h;
}				t_map;

typedef struct s_color
{
	unsigned int floor;
	unsigned int ceiling;
}				t_color;

typedef struct s_texture
{
	char *north;
	char *south;
	char *west;
	char *east;	
}			t_texture;

typedef struct s_game
{
	void *mlx;
	void *win;
	void *img;
	char *str_map;
	// t_player player;
	// t_buffer *lst_buffer;
	t_color	color;
	t_texture	texture;
	// t_mouse mouse;
	t_map map;
}			t_game;


// get_data
int get_map(char *file, t_game *game);
int get_textures(t_game *game);
int get_colors(t_game *game);

// parsing
int parse_map(char **map);
int len_max(char **str);
int     find_x(char **map, int i);
int     find_y(char **map, int i);
unsigned int rgba_to_hex(char *color, int *overflow);
void	cut_map(t_game *game);


void print_texture(t_texture t);

#endif