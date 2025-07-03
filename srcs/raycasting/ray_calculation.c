/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:30:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 03:36:51 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

t_ray	get_init_ray(float cos_a, float sin_a, double x, double y)
{
	t_ray	ray;

	if (cos_a > 0)
		ray.st_cos.x = floor(x + 1) - x;
	else
		ray.st_cos.x = ceil(x - 1) - x;
	ray.st_cos.y = ray.st_cos.x * (sin_a / cos_a);
	ray.ln_cos = calc_sqrtlen(ray.st_cos);
	if (sin_a > 0)
		ray.st_sin.y = floor(y + 1) - y;
	else
		ray.st_sin.y = ceil(y - 1) - y;
	ray.st_sin.x = ray.st_sin.y * (cos_a / sin_a);
	ray.ln_sin = calc_sqrtlen(ray.st_sin);
	return (ray);
}

float	calc_tex_offset(t_trace *tr)
{
	double	offset;

	if (tr->ray.ln_cos < tr->ray.ln_sin)
	{
		offset = tr->ref.x + tr->ref.y + tr->ray.st_cos.x + tr->ray.st_cos.y;
		offset -= (int)offset;
		if (tr->cos_a < 0)
			offset = 1 - offset;
	}
	else
	{
		offset = tr->ref.x + tr->ref.y + tr->ray.st_sin.x + tr->ray.st_sin.y;
		offset -= (int)offset;
		if (tr->sin_a > 0)
			offset = 1 - offset;
	}
	return ((float)offset);
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

void	handle_wall_hit(t_trace *tr)
{
	tr->len = fmin(tr->ray.ln_cos, tr->ray.ln_sin);
	tr->tex_offset = calc_tex_offset(tr);
}

void	handle_max_steps_reached(t_trace *tr, int max_steps)
{
	tr->len = max_steps;
	tr->wall_side = 0;
	tr->tex_offset = 0;
	tr->map_x = 0;
	tr->map_y = 0;
}
