/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:43:09 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/26 13:55:07 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define WALL '1'
#define EMPTY '0'
#define VISITED 'F'


// Reset
#define RESET       "\033[0m"

// Regular Colors
#define BLACK       "\033[0;30m"
#define RED         "\033[0;31m"
#define GREEN       "\033[0;32m"
#define YELLOW      "\033[0;33m"
#define BLUE        "\033[0;34m"
#define MAGENTA     "\033[0;35m"
#define CYAN        "\033[0;36m"
#define WHITE       "\033[0;37m"

// Bold
#define BBLACK      "\033[1;30m"
#define BRED        "\033[1;31m"
#define BGREEN      "\033[1;32m"
#define BYELLOW     "\033[1;33m"
#define BBLUE       "\033[1;34m"
#define BMAGENTA    "\033[1;35m"
#define BCYAN       "\033[1;36m"
#define BWHITE      "\033[1;37m"

#include "../MacroLibX/includes/mlx.h"
#include "raycasting.h"
#include <stdio.h>
#include <fcntl.h>
# include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "../lib/libft/libft.h"
#include "../lib/printf_fd/ft_printf.h"
#include "../lib/gnl/get_next_line.h"

#include "../lib/MacroLibX/includes/mlx.h"
#include "../lib/MacroLibX/includes/mlx_extended.h"

// Forward declarations - les vraies structures sont dans raycasting.h
typedef struct s_map t_map;
typedef struct s_color t_color;
typedef struct s_texture t_texture;
typedef struct s_game t_game;


// get_data
int get_map(char *file, t_game *game);
int get_textures(t_game *game);
int get_colors(t_game *game);

// parsing
int parse_map(char **map, t_game *game);
int len_max(char **str);
int     find_x(char **map, int i);
int     find_y(char **map, int i);
mlx_color rgba_to_hex(char *color, int *overflow);
int	cut_map(t_game *game);
int count_occurrences(char *key, char **map);
int    parse_occu(char **map);

//utils
void	custom_occu_print(char *key, char **map);

void print_texture(t_texture t);

#endif