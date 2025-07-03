/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:30:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 03:44:13 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

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
	return (result);
}

t_ray	cast_ray_corrected(t_game *game, float angle, float relative_angle)
{
	t_trace	tr;
	int			max_steps;
	int			i;

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
	return (cast_ray_corrected(game, angle, angle - game->player.angle));
}

void	process_column(t_game *game, int x, t_render_params params)
{
	float	camera_x;
	float	ray_angle;
	t_ray	ray;
	float	wall_height;

	camera_x = 2 * x / (float)WIDTH - 1;
	ray_angle = game->player.angle + atan(camera_x * params.tan_fov_half);
	ray = cast_ray_corrected(game, ray_angle, camera_x * params.tan_fov_half);
	wall_height = params.wall_scale / ray.dist;
	if (wall_height > HEIGHT * 5)
		wall_height = HEIGHT * 5;
	if (wall_height < 1.0f)
		wall_height = 1.0f;
	draw_vertical_line_no_stretch(game, x, wall_height, ray);
}

void	render_frame(t_game *game)
{
	int				x;
	t_render_params	params;

	params.fov_half = PI / 6.0f;
	params.tan_fov_half = tan(params.fov_half);
	params.wall_scale = BLOCK_SIZE * (WIDTH / 2.0f) / params.tan_fov_half;
	x = 0;
	while (x < WIDTH)
	{
		process_column(game, x, params);
		x++;
	}
	mlx_pixel_put_region(game->mlx, game->win, 0, 0, WIDTH, HEIGHT,
		game->frame_buffer);
}
