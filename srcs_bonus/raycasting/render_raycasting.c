/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:51:16 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 11:51:47 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	make_sprite(t_game *game)
{
	static bool	has_exit[2] = {false, false};
	bool		is_moving;

	is_moving = game->player.key_up || game->player.key_down
		|| game->player.key_left || game->player.key_right;
	if (game->bar.valid[1] && game->bar.valid[2]
		&& game->bar.valid[3] && !game->bar.wheel)
	{
		if (is_moving && !has_exit[0])
			draw_exit_kunai(game, &has_exit[0]);
		if (has_exit[0])
		{
			if (!has_exit[1])
				draw_transition(game, &has_exit[1]);
			else
				draw_sprinting_kunai(game, is_moving);
		}
		if (!is_moving)
		{
			has_exit[0] = false;
			has_exit[1] = false;
		}
	}
	else if (game->bar.valid[0] && game->bar.wheel)
		draw_crow(game);
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

void	render_frameranche(t_game *game)
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
	make_sprite(game);
	mlx_pixel_put_region(game->mlx, game->win, 0, 0,
		WIDTH, HEIGHT, game->frame_buffer);
}
