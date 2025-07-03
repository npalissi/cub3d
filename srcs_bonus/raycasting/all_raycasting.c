/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:54:03 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 11:54:17 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	handle_max_steps_reached(t_trace *tr, int max_steps)
{
	tr->len = max_steps;
	tr->wall_side = 0;
	tr->tex_offset = 0;
	tr->map_x = 0;
	tr->map_y = 0;
}

t_ray	create_result(t_game *game, t_trace *tr)
{
	t_ray	result;

	tr->len = tr->len / sqrt(1 + tr->newa * tr->newa);
	result.dist = tr->len * BLOCK_SIZE;
	result.wall_side = tr->wall_side;
	result.wall_x = tr->tex_offset;
	result.cos_angle = tr->cos_a;
	result.sin_angle = tr->sin_a;
	result.x = game->player.x + tr->cos_a * result.dist;
	result.y = game->player.y + tr->sin_a * result.dist;
	result.is_vertical = !(tr->wall_side == 2 || tr->wall_side == 3);
	result.is_door = is_door_at_position(game, tr->map_x, tr->map_y);
	return (result);
}

void	handle_wall_hit(t_trace *tr)
{
	tr->len = fmin(tr->ray.ln_cos, tr->ray.ln_sin);
	tr->tex_offset = calc_tex_offset(tr);
}

t_ray	cast_ray_corrected(t_game *game, float angle, float relative_angle)
{
	t_trace	tr;
	int		max_steps;
	int		i;

	tr = init_trace(game, angle, relative_angle);
	max_steps = get_max_steps(game);
	i = 0;
	while (i < max_steps)
	{
		get_collide_pos(&tr);
		if (check_wall(game, tr.map_x, tr.map_y))
		{
			handle_wall_hit(&tr);
			break ;
		}
		cast_forward(&tr.ray, &tr.step);
		i++;
	}
	if (i >= max_steps)
		handle_max_steps_reached(&tr, max_steps);
	return (create_result(game, &tr));
}

t_ray	cast_ray(t_game *game, float angle)
{
	float	relative_angle;

	relative_angle = angle - game->player.angle;
	return (cast_ray_corrected(game, angle, relative_angle));
}
