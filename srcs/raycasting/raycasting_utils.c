/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/25 11:10:24 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

static float	get_horizontal_dist(t_game *game, float angle)
{
	float	ray_x;
	float	ray_y;
	float	y_step;
	float	x_step;

	if (fabs(sin(angle)) < 0.0001)
		return (INFINITY);
	if (sin(angle) > 0)
		y_step = BLOCK_SIZE;
	else
		y_step = -BLOCK_SIZE;
	x_step = y_step / tan(angle);
	ray_y = get_ray_pos_y(game, angle);
	ray_x = game->player.x + (ray_y - game->player.y) / tan(angle);
	while (!is_wall_hit(game, ray_x, ray_y))
	{
		ray_x += x_step;
		ray_y += y_step;
	}
	return (calculate_distance(game, ray_x, ray_y));
}

static float	get_vertical_dist(t_game *game, float angle)
{
	float	ray_x;
	float	ray_y;
	float	x_step;
	float	y_step;

	if (fabs(cos(angle)) < 0.0001)
		return (INFINITY);
	if (cos(angle) > 0)
		x_step = BLOCK_SIZE;
	else
		x_step = -BLOCK_SIZE;
	y_step = x_step * tan(angle);
	ray_x = get_ray_pos_x(game, angle);
	ray_y = game->player.y + (ray_x - game->player.x) * tan(angle);
	while (!is_wall_hit(game, ray_x, ray_y))
	{
		ray_x += x_step;
		ray_y += y_step;
	}
	return (calculate_distance(game, ray_x, ray_y));
}

t_ray	cast_ray(t_game *game, float angle)
{
	t_ray	ray;
	float	h_dist;
	float	v_dist;
	float	hit_x, hit_y;

	h_dist = get_horizontal_dist(game, angle);
	v_dist = get_vertical_dist(game, angle);
	
	if (h_dist < v_dist)
	{
		ray.dist = h_dist;
		ray.is_vertical = 0;
		// Calcul de la position du hit pour les murs horizontaux
		hit_x = game->player.x + cos(angle) * h_dist;
		hit_y = game->player.y + sin(angle) * h_dist;
		
		// Déterminer si c'est un mur nord ou sud
		if (sin(angle) > 0)
			ray.wall_side = 1;  // Sud (on regarde vers le bas)
		else
			ray.wall_side = 0;  // Nord (on regarde vers le haut)
		
		// Position x sur le mur pour la texture
		ray.wall_x = fmod(hit_x, BLOCK_SIZE) / BLOCK_SIZE;
	}
	else
	{
		ray.dist = v_dist;
		ray.is_vertical = 1;
		// Calcul de la position du hit pour les murs verticaux
		hit_x = game->player.x + cos(angle) * v_dist;
		hit_y = game->player.y + sin(angle) * v_dist;
		
		// Déterminer si c'est un mur est ou ouest
		if (cos(angle) > 0)
			ray.wall_side = 3;  // Est (on regarde vers la droite)
		else
			ray.wall_side = 2;  // Ouest (on regarde vers la gauche)
		
		// Position y sur le mur pour la texture
		ray.wall_x = fmod(hit_y, BLOCK_SIZE) / BLOCK_SIZE;
	}
	
	ray.x = hit_x;
	ray.y = hit_y;
	ray.dist = ray.dist * cos(angle - game->player.angle);
	ray.cos_angle = cos(angle);
	ray.sin_angle = sin(angle);
	return (ray);
}
