/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:43:09 by npalissi          #+#    #+#             */
/*   Updated: 2025/05/07 14:12:06 by edubois-         ###   ########.fr       */
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

// get_data
int get_map(char *file, char ***map);
int get_textures(char ***map, int *fd);

// parsing
int parse_map(char **map);
int len_max(char **str);
int     find_x(char **map, int i);
int     find_y(char **map, int i);

#endif