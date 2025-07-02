/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/25 11:10:20 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

float	get_ray_pos_y(t_game *game, float angle)
{
	if (sin(angle) > 0)
		return ((int)(game->player.y / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE);
	else
		return ((int)(game->player.y / BLOCK_SIZE) * BLOCK_SIZE - 0.0001f);
}

float	get_ray_pos_x(t_game *game, float angle)
{
	if (cos(angle) > 0)
		return ((int)(game->player.x / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE);
	else
		return ((int)(game->player.x / BLOCK_SIZE) * BLOCK_SIZE - 0.0001f);
}

float	calculate_distance(t_game *game, float ray_x, float ray_y)
{
	float	dx;
	float	dy;

	dx = ray_x - game->player.x;
	dy = ray_y - game->player.y;
	return (sqrt(dx * dx + dy * dy));
}

// Fonction pour vérifier si une position correspond à une porte
int is_door_at_position(t_game *game, int map_x, int map_y)
{
	int i;

	if (!game->d)
		return (0);
	
	i = 0;
	while (game->d[i].x)
	{
		if (game->d[i].x == map_x && game->d[i].y == map_y)
			return (1);
		i++;
	}
	return (0);
}

int	is_wall_hit(t_game *game, float ray_x, float ray_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(ray_x / BLOCK_SIZE);
	map_y = (int)(ray_y / BLOCK_SIZE);
	
	if (map_x < 0 || map_x >= game->map.w || map_y < 0 || map_y >= game->map.h)
		return (1);
	if (!game->map.map || !game->map.map[map_y])
		return (1);
	return (game->map.map[map_y][map_x] == '1');
}
