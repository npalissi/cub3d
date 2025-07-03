/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:49:42 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 11:50:18 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

int	is_door_at_position(t_game *game, int map_x, int map_y)
{
	int	i;

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

void	get_collide_pos(t_trace *tr)
{
	if (tr->ray.ln_cos > tr->ray.ln_sin)
	{
		tr->map_x = floor(tr->ref.x + tr->ray.st_sin.x);
		tr->map_y = floor(tr->ref.y + tr->ray.st_sin.y + tr->sin_a / 2);
		tr->wall_side = (tr->sin_a > 0);
	}
	else
	{
		tr->map_x = floor(tr->ref.x + tr->ray.st_cos.x + tr->cos_a / 2);
		tr->map_y = floor(tr->ref.y + tr->ray.st_cos.y);
		tr->wall_side = (tr->cos_a > 0) + 2;
	}
}

t_trace	init_trace(t_game *game, float angle, float relative_angle)
{
	t_trace	tr;

	tr.cos_a = cos(angle);
	tr.sin_a = sin(angle);
	tr.newa = relative_angle;
	tr.ref.x = game->player.x / BLOCK_SIZE;
	tr.ref.y = game->player.y / BLOCK_SIZE;
	tr.ray = get_init_ray(tr.cos_a, tr.sin_a, tr.ref.x, tr.ref.y);
	tr.step = get_init_ray(tr.cos_a, tr.sin_a, 0, 0);
	return (tr);
}

int	get_max_steps(t_game *game)
{
	int	max_steps;

	if (game->map.w > game->map.h)
		max_steps = game->map.w;
	else
		max_steps = game->map.h;
	return (max_steps * 2 + 10);
}
