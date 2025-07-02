/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/01 10:10:45 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

// DDA Algorithm optimisé inspiré de Lodev
static t_ray	cast_ray_dda(t_game *game, float angle)
{
	t_ray	ray;
	float	ray_dir_x, ray_dir_y;
	int		map_x, map_y;
	float	delta_dist_x, delta_dist_y;
	float	side_dist_x, side_dist_y;
	int		step_x, step_y;
	int		hit, side;
	float	perp_wall_dist;

	// Direction du rayon
	ray_dir_x = cos(angle);
	ray_dir_y = sin(angle);
	
	// Position actuelle sur la grille
	map_x = (int)(game->player.x / BLOCK_SIZE);
	map_y = (int)(game->player.y / BLOCK_SIZE);
	
	// Calcul des distances delta (optimisation clé)
	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0f / ray_dir_x);
	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0f / ray_dir_y);
	
	// Calcul de step et side_dist initiale
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (game->player.x / BLOCK_SIZE - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0f - game->player.x / BLOCK_SIZE) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (game->player.y / BLOCK_SIZE - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0f - game->player.y / BLOCK_SIZE) * delta_dist_y;
	}
	
	// DDA - Boucle optimisée
	hit = 0;
	while (hit == 0)
	{
		// Vérification des limites de carte en premier (optimisation)
		if (map_x < 0 || map_x >= game->map.w || map_y < 0 || map_y >= game->map.h)
		{
			hit = 1;
			side = (side_dist_x < side_dist_y) ? 0 : 1;
			break;
		}
		
		// Saut au prochain côté de grille
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		
		// Vérification de collision mur
		if (game->map.map && game->map.map[map_y] && game->map.map[map_y][map_x] == '1')
			hit = 1;
	}
	
	// Calcul de la distance perpendiculaire (évite fisheye)
	if (side == 0)
		perp_wall_dist = (map_x - game->player.x / BLOCK_SIZE + (1 - step_x) / 2) / ray_dir_x;
	else
		perp_wall_dist = (map_y - game->player.y / BLOCK_SIZE + (1 - step_y) / 2) / ray_dir_y;
	
	// Remplissage de la structure ray
	ray.dist = perp_wall_dist * BLOCK_SIZE;
	ray.is_vertical = side;
	ray.cos_angle = ray_dir_x;
	ray.sin_angle = ray_dir_y;
	
	// Calcul des coordonnées du hit
	ray.x = game->player.x + ray_dir_x * ray.dist;
	ray.y = game->player.y + ray_dir_y * ray.dist;
	
	// Détection si c'est une porte
	ray.is_door = is_door_at_position(game, map_x, map_y);
	
	// Détermination du côté du mur et coordonnée texture
	if (side == 0)  // Mur vertical
	{
		if (ray_dir_x > 0)
			ray.wall_side = 3;  // Est
		else
			ray.wall_side = 2;  // Ouest
		ray.wall_x = fmod(ray.y, BLOCK_SIZE) / BLOCK_SIZE;
	}
	else  // Mur horizontal
	{
		if (ray_dir_y > 0)
			ray.wall_side = 1;  // Sud
		else
			ray.wall_side = 0;  // Nord
		ray.wall_x = fmod(ray.x, BLOCK_SIZE) / BLOCK_SIZE;
	}
	
	return (ray);
}

// Fonction DDA optimisée avec early termination
static t_ray	cast_ray_dda_optimized(t_game *game, float angle)
{
	t_ray	ray;
	float	ray_dir_x, ray_dir_y;
	int		map_x, map_y;
	float	delta_dist_x, delta_dist_y;
	float	side_dist_x, side_dist_y;
	int		step_x, step_y;
	int		hit, side;
	float	perp_wall_dist;
	int		max_distance;

	// Direction du rayon normalisée
	ray_dir_x = cos(angle);
	ray_dir_y = sin(angle);
	
	// Position initiale sur la grille
	map_x = (int)(game->player.x / BLOCK_SIZE);
	map_y = (int)(game->player.y / BLOCK_SIZE);
	
	// Distance maximale de rendu (optimisation)
	max_distance = (game->map.w > game->map.h) ? game->map.w : game->map.h;
	max_distance += 10; // Marge de sécurité
	
	// Précalcul des distances delta (évite divisions répétées)
	if (ray_dir_x == 0)
		delta_dist_x = 1e30;
	else
		delta_dist_x = fabs(1.0f / ray_dir_x);
	if (ray_dir_y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(1.0f / ray_dir_y);
	
	// Setup initial pour DDA
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (game->player.x / BLOCK_SIZE - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0f - game->player.x / BLOCK_SIZE) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (game->player.y / BLOCK_SIZE - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0f - game->player.y / BLOCK_SIZE) * delta_dist_y;
	}
	
	// DDA avec optimisations
	hit = 0;
	int iterations = 0;
	while (hit == 0 && iterations < max_distance)
	{
		// Early termination si hors limites
		if (map_x < 0 || map_x >= game->map.w || map_y < 0 || map_y >= game->map.h)
		{
			hit = 1;
			side = (side_dist_x < side_dist_y) ? 0 : 1;
			break;
		}
		
		// Mouvement DDA optimisé
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		
		// Test de collision avec validation sécurisée
		if (map_x >= 0 && map_x < game->map.w && map_y >= 0 && map_y < game->map.h &&
			game->map.map && game->map.map[map_y] && game->map.map[map_y][map_x] == '1')
			hit = 1;
		
		iterations++;
	}
	
	// Calcul distance perpendiculaire (correction fisheye)
	if (side == 0)
		perp_wall_dist = (map_x - game->player.x / BLOCK_SIZE + (1 - step_x) / 2) / ray_dir_x;
	else
		perp_wall_dist = (map_y - game->player.y / BLOCK_SIZE + (1 - step_y) / 2) / ray_dir_y;
	
	// Assemblage final du ray
	ray.dist = perp_wall_dist * BLOCK_SIZE;
	ray.is_vertical = side;
	ray.cos_angle = ray_dir_x;
	ray.sin_angle = ray_dir_y;
	
	// Coordonnées exactes du hit
	ray.x = game->player.x + ray_dir_x * ray.dist;
	ray.y = game->player.y + ray_dir_y * ray.dist;
	
	// Détection si c'est une porte
	ray.is_door = is_door_at_position(game, map_x, map_y);
	
	// Side et coordonnée texture optimisés
	if (side == 0)  // Vertical hit
	{
		ray.wall_side = (ray_dir_x > 0) ? 3 : 2;  // Est : Ouest
		ray.wall_x = fmod(ray.y, BLOCK_SIZE) / BLOCK_SIZE;
		if (ray.wall_x < 0) ray.wall_x += 1.0f;
	}
	else  // Horizontal hit
	{
		ray.wall_side = (ray_dir_y > 0) ? 1 : 0;  // Sud : Nord
		ray.wall_x = fmod(ray.x, BLOCK_SIZE) / BLOCK_SIZE;
		if (ray.wall_x < 0) ray.wall_x += 1.0f;
	}
	
	return (ray);
}

// Nouvelle fonction cast_ray utilisant l'algorithme DDA optimisé
t_ray	cast_ray(t_game *game, float angle)
{
	t_ray ray;
	
	// Utiliser l'algorithme DDA optimisé
	ray = cast_ray_dda_optimized(game, angle);
	
	// Correction fisheye (déjà incluse dans DDA mais on s'assure)
	ray.dist = ray.dist * cos(angle - game->player.angle);
	
	return (ray);
}
