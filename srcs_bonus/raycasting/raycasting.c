/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:32:11 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 11:58:54 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

static double	calc_sqrtlen(t_vecd v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

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

int	check_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.w || y < 0 || y >= game->map.h)
		return (1);
	if (!game->map.map || !game->map.map[y])
		return (1);
	return (game->map.map[y][x] == '1');
}
