/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/24 17:13:58 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

static void	init_render_data(t_render_data *data)
{
	data->fov_half = PI / 6;
	data->angle_step = (PI / 3) / WIDTH;
	data->projection_dist = (WIDTH / 2) / tan(data->fov_half);
}

static void	process_ray(t_game *game, t_render_data *data, int x)
{
	data->ray_angle = game->player.angle - data->fov_half
		+ (x * data->angle_step);
	data->ray = cast_ray(game, data->ray_angle);
	if (data->ray.dist == INFINITY || data->ray.dist <= 0)
		data->ray.dist = 1000.0f;
	data->wall_height = (BLOCK_SIZE * data->projection_dist) / data->ray.dist;
	if (data->wall_height > HEIGHT * 2)
		data->wall_height = HEIGHT * 2;
}

void	render_frame(t_game *game)
{
	t_render_data	data;
	int				x;

	init_render_data(&data);
	x = 0;
	while (x < WIDTH)
	{
		process_ray(game, &data, x);
		draw_vertical_line(game, x, data.wall_height, data.ray);
		x++;
	}
	mlx_pixel_put_region(game->mlx, game->win, 0, 0, WIDTH, HEIGHT, game->frame_buffer);
}
