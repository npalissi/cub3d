/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:30:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 03:37:25 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

double	calc_sqrtlen(t_vecd v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

int	check_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.w || y < 0 || y >= game->map.h)
		return (1);
	if (!game->map.map || !game->map.map[y])
		return (1);
	return (game->map.map[y][x] == '1');
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

void	cast_forward(t_ray *ray, t_ray *step)
{
	if (ray->ln_cos < ray->ln_sin)
	{
		ray->st_cos.x += step->st_cos.x;
		ray->st_cos.y += step->st_cos.y;
		ray->ln_cos += step->ln_cos;
	}
	else
	{
		ray->st_sin.x += step->st_sin.x;
		ray->st_sin.y += step->st_sin.y;
		ray->ln_sin += step->ln_sin;
	}
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
