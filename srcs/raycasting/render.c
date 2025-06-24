/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/23 20:16:09 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

static mlx_color	get_texture_color(t_game *game, t_ray ray, int tex_y)
{
	mlx_image texture;
	int tex_x;
	mlx_color color;
	
	// Choisir la bonne texture selon l'orientation du mur
	if (ray.wall_side == 0)  // Nord
		texture = game->texture.north_img;
	else if (ray.wall_side == 1)  // Sud
		texture = game->texture.south_img;
	else if (ray.wall_side == 2)  // Ouest
		texture = game->texture.west_img;
	else  // Est
		texture = game->texture.east_img;
	
	// Vérifier si la texture est valide
	if (!texture)
	{
		color.r = 255;
		color.g = 0;
		color.b = 255;
		color.a = 255;
		return (color);
	}
	
	// Calculer la coordonnée X de la texture (0 à width-1)
	tex_x = (int)(ray.wall_x * game->texture.width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= game->texture.width)
		tex_x = game->texture.width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= game->texture.height)
		tex_y = game->texture.height - 1;
	
	// Récupérer la couleur du pixel de la texture
	color = mlx_get_image_pixel(game->mlx, texture, tex_x, tex_y);
	return (color);
}

void	draw_vertical_line(t_game *game, int x, float wall_height, t_ray ray)
{
	int	start_y;
	int	end_y;
	int	y;
	int	tex_y;
	float	step;
	float	tex_pos;

	start_y = (HEIGHT - (int)wall_height) / 2;
	end_y = start_y + (int)wall_height;
	if (start_y < 0)
		start_y = 0;
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	
	// Dessiner le plafond
	y = 0;
	while (y < start_y)
	{
		game->frame_buffer[y * WIDTH + x] = game->color.ceiling;
		y++;
	}
	
	// Dessiner le mur avec texture
	step = (float)game->texture.height / wall_height;
	tex_pos = (start_y - (HEIGHT - wall_height) / 2) * step;
	
	y = start_y;
	while (y < end_y)
	{
		tex_y = (int)tex_pos;
		game->frame_buffer[y * WIDTH + x] = get_texture_color(game, ray, tex_y);
		tex_pos += step;
		y++;
	}
	
	// Dessiner le sol
	while (y < HEIGHT)
	{
		game->frame_buffer[y * WIDTH + x] = game->color.floor;
		y++;
	}
}
