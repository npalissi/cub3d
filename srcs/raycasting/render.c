/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/01 10:27:09 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

// Tableau de pointeurs pour accès direct aux textures (optimisation)
static mlx_image	*get_texture_fast(t_game *game, int wall_side)
{
	static mlx_image *textures[4] = {NULL};
	static int initialized = 0;
	
	// Initialisation paresseuse du cache
	if (!initialized)
	{
		textures[0] = &game->texture.north_img;
		textures[1] = &game->texture.south_img;
		textures[2] = &game->texture.west_img;
		textures[3] = &game->texture.east_img;
		initialized = 1;
	}
	
	// Accès direct par index (plus rapide que switch/if)
	return (textures[wall_side]);
}

// Version optimisée du calcul de couleur texture avec support des portes
static mlx_color	get_texture_color_optimized(t_game *game, t_ray ray, int tex_y)
{
	mlx_image *texture;
	int tex_x;
	mlx_color color;
	
	// Si c'est une porte, utiliser la texture de porte
	if (ray.is_door)
	{
		texture = &game->texture.door_img;
	}
	else
	{
		// Accès rapide à la texture normale
		texture = get_texture_fast(game, ray.wall_side);
	}
	
	// Vérification de validité avec couleur d'erreur par défaut
	if (!texture || !*texture)
	{
		color.rgba = 0xFF00FFFF; // Magenta avec alpha
		return (color);
	}
	
	// Calcul optimisé des coordonnées texture avec clamping
	tex_x = (int)(ray.wall_x * game->texture.width);
	tex_x = (tex_x < 0) ? 0 : (tex_x >= game->texture.width) ? game->texture.width - 1 : tex_x;
	tex_y = (tex_y < 0) ? 0 : (tex_y >= game->texture.height) ? game->texture.height - 1 : tex_y;
	
	// Récupération pixel avec validation
	color = mlx_get_image_pixel(game->mlx, *texture, tex_x, tex_y);
	return (color);
}

// Fonction de fallback pour compatibilité
static mlx_color	get_texture_color(t_game *game, t_ray ray, int tex_y)
{
	return (get_texture_color_optimized(game, ray, tex_y));
}

// Version optimisée du rendu de ligne verticale
void	draw_vertical_line_optimized(t_game *game, int x, float wall_height, t_ray ray)
{
	int		start_y, end_y, y;
	int		tex_y;
	float	step, tex_pos;
	int		buffer_offset;
	mlx_color	*frame_ptr;
	mlx_color	ceiling_color, floor_color;
	
	// Précalculs pour optimisation
	start_y = (HEIGHT - (int)wall_height) / 2;
	end_y = start_y + (int)wall_height;
	start_y = (start_y < 0) ? 0 : start_y;
	end_y = (end_y > HEIGHT) ? HEIGHT : end_y;
	
	// Cache des couleurs pour éviter les accès répétés
	ceiling_color = game->color.ceiling;
	floor_color = game->color.floor;
	
	// Pointeur de base pour accès direct au frame buffer
	frame_ptr = game->frame_buffer + x;
	
	// Rendu plafond optimisé (accès mémoire linéaire)
	for (y = 0; y < start_y; y++)
	{
		frame_ptr[y * WIDTH] = ceiling_color;
	}
	
	// Rendu mur avec texture - calculs corrigés pour éviter étirement
	step = (float)game->texture.height / wall_height;
	
	// Calcul corrigé de tex_pos pour éviter décalage
	// Quand le mur est très grand, on doit commencer depuis le haut de la texture
	float tex_start;
	if (wall_height > HEIGHT) {
		// Pour les murs très hauts, calculer où commencer dans la texture
		float wall_start = (HEIGHT - wall_height) / 2.0f;
		tex_start = (start_y - wall_start) * step;
	} else {
		// Pour les murs normaux, commencer au début de la texture
		tex_start = 0.0f;
	}
	
	tex_pos = tex_start;
	
	// Boucle déroulée pour le rendu du mur (optimisation critique)
	for (y = start_y; y < end_y; y++)
	{
		tex_y = (int)tex_pos;
		// S'assurer que tex_y reste dans les limites
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= game->texture.height) tex_y = game->texture.height - 1;
		
		buffer_offset = y * WIDTH;
		frame_ptr[buffer_offset] = get_texture_color_optimized(game, ray, tex_y);
		tex_pos += step;
	}
	
	// Rendu sol optimisé
	for (y = end_y; y < HEIGHT; y++)
	{
		frame_ptr[y * WIDTH] = floor_color;
	}
}

// Version alternative sans déformation pour tests
void	draw_vertical_line_no_stretch(t_game *game, int x, float wall_height, t_ray ray)
{
	int		start_y, end_y, y;
	int		tex_y;
	float	step, tex_pos;
	mlx_color	ceiling_color, floor_color;
	
	// Calculs de base
	start_y = (HEIGHT - (int)wall_height) / 2;
	end_y = start_y + (int)wall_height;
	start_y = (start_y < 0) ? 0 : start_y;
	end_y = (end_y > HEIGHT) ? HEIGHT : end_y;
	
	ceiling_color = game->color.ceiling;
	floor_color = game->color.floor;
	
	// Rendu plafond
	for (y = 0; y < start_y; y++)
		game->frame_buffer[y * WIDTH + x] = ceiling_color;
	
	// Calcul améliorer pour texture mapping
	step = (float)game->texture.height / wall_height;
	
	// Position de départ dans la texture corrigée
	if (wall_height > HEIGHT) {
		// Pour les murs très hauts, calculer l'offset correct
		float pixels_off_screen = (wall_height - HEIGHT) / 2.0f;
		tex_pos = pixels_off_screen * step;
	} else {
		tex_pos = 0.0f;
	}
	
	// Rendu du mur avec texture
	for (y = start_y; y < end_y; y++)
	{
		tex_y = (int)tex_pos;
		// Clamping sécurisé
		tex_y = (tex_y < 0) ? 0 : tex_y;
		tex_y = (tex_y >= game->texture.height) ? game->texture.height - 1 : tex_y;
		
		game->frame_buffer[y * WIDTH + x] = get_texture_color_optimized(game, ray, tex_y);
		tex_pos += step;
	}
	
	// Rendu sol
	for (y = end_y; y < HEIGHT; y++)
		game->frame_buffer[y * WIDTH + x] = floor_color;
}

// Version compatible pour l'API existante
void	draw_vertical_line(t_game *game, int x, float wall_height, t_ray ray)
{
	// Utiliser la version corrigée pour éviter l'étirement
	draw_vertical_line_no_stretch(game, x, wall_height, ray);
}
