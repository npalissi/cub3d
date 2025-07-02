/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/02 22:06:18 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

// Fonction pour obtenir la texture appropriée selon le côté du mur
static mlx_image	*get_wall_texture(t_game *game, t_ray ray)
{
	if (ray.is_door && game->texture.door_img)
		return (&game->texture.door_img);
	
	if (ray.wall_side == 0)
		return (&game->texture.north_img);
	else if (ray.wall_side == 1)
		return (&game->texture.south_img);
	else if (ray.wall_side == 2)
		return (&game->texture.west_img);
	else
		return (&game->texture.east_img);
}

// Fonction de rendu de ligne verticale optimisée pour ttranche
void	draw_vertical_line_no_stretch(t_game *game, int x, float wall_height, t_ray ray)
{
	int		start_y, end_y, y;
	int		tex_y, tex_x;
	float	step, tex_pos;
	mlx_color	*column;
	mlx_image	*texture;
	
	// Calculs de base
	start_y = (HEIGHT - (int)wall_height) / 2;
	end_y = start_y + (int)wall_height;
	start_y = (start_y < 0) ? 0 : start_y;
	end_y = (end_y > HEIGHT) ? HEIGHT : end_y;
	
	// Pointeur direct vers la colonne
	column = game->frame_buffer + x;
	
	// Rendu plafond
	for (y = 0; y < start_y; y++)
		column[y * WIDTH] = game->color.ceiling;
	
	// Sélectionner la texture
	texture = get_wall_texture(game, ray);
	if (!texture || !*texture)
	{
		// Couleur d'erreur si texture manquante
		mlx_color error_color = {{255, 255, 0, 255}};  // Jaune
		for (y = start_y; y < end_y; y++)
			column[y * WIDTH] = error_color;
	}
	else
	{
		// Calculs pour texture mapping
		step = (float)game->texture.height / wall_height;
		tex_x = (int)(ray.wall_x * game->texture.width);
		tex_x = (tex_x < 0) ? 0 : (tex_x >= game->texture.width) ? game->texture.width - 1 : tex_x;
		
		// Position de départ dans la texture
		if (wall_height > HEIGHT) {
			float pixels_off_screen = (wall_height - HEIGHT) / 2.0f;
			tex_pos = pixels_off_screen * step;
		} else {
			tex_pos = 0.0f;
		}
		
		// Rendu du mur avec texture
		for (y = start_y; y < end_y; y++)
		{
			tex_y = (int)tex_pos;
			tex_y = (tex_y < 0) ? 0 : (tex_y >= game->texture.height) ? game->texture.height - 1 : tex_y;
			
			mlx_color color = mlx_get_image_pixel(game->mlx, *texture, tex_x, tex_y);
			column[y * WIDTH] = color;
			
			tex_pos += step;
		}
	}
	
	// Rendu sol
	for (y = end_y; y < HEIGHT; y++)
		column[y * WIDTH] = game->color.floor;
}

// Fonction principale de rendu - utilise uniquement ttranche
void	render_frame(t_game *game)
{
	render_frame_ttranche(game);
}