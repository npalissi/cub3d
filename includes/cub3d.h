/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:43:09 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/25 19:44:53 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include "../MacroLibX/includes/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "../lib/libft/libft.h"

typedef struct	s_buffer
{
	char			buffer[5];
	struct s_buffer	*next;

}				t_buffer;

typedef struct s_color
{
	char *floor;
	char *ceiling;
}				t_color;


typedef struct s_mat
{
	char *north;
	char *south;
	char *west;
	char *east;	
}			t_mat;




typedef struct s_game
{
	void *mlx;
	void *win;
	void *img;
	char *str_map;
	t_buffer *lst_buffer;
	t_color	color;
	t_mat	mat;
}			t_game;

char *recover_file(t_game *game, char *name_file);
int init_data(t_game *game);

#endif