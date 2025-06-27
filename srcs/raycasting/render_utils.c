/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/27 16:03:50 by edubois-         ###   ########.fr       */
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
	
	// Vérification de distance valide
	if (data->ray.dist == INFINITY || data->ray.dist <= 0)
		data->ray.dist = 1000.0f;
	
	// La correction fish-eye est déjà appliquée dans cast_ray()
	// Pas besoin de correction supplémentaire ici
	
	// Distance minimale pour éviter les bugs quand on est très proche
	if (data->ray.dist < 1.0f)
		data->ray.dist = 1.0f;
	
	// Calcul de la hauteur du mur
	data->wall_height = (BLOCK_SIZE * data->projection_dist) / data->ray.dist;
	
	// Limitation plus raisonnable de la hauteur
	if (data->wall_height > HEIGHT * 3)
		data->wall_height = HEIGHT * 3;
}


typedef struct 
{
	uint32_t x;
	uint32_t y;
}	vec2;

void put_region_to_array(mlx_color *fb, vec2 start, vec2 size, mlx_color *src)
{
	for (uint32_t y = 0; y < size.y; ++y)
	{
		for (uint32_t x = 0; x < size.x; ++x)
		{
			uint32_t sindex = y * size.x + x; // source = tmp[y][x]
			uint32_t index = (start.y + y) * WIDTH + (start.x + x); // dest = fb[y+start.y][x+start.x]

			if (!src[sindex].a)
				continue;
			fb[index] = src[sindex];
		}
	}
}


void	draw_crow(t_game *game)
{
	static mlx_color	tmp[WIDTH * HEIGHT] = {0};

	// mlx_put_image_to_window(game->mlx, game->win, game->bar.bar, 0, 0);
	static int i = 1;
	static int dir = 1; // 1 = forward, -1 = backward
	
	if (current_time() - game->bar.time > 200 && (game->player.key_up ||game->player.key_down|| game->player.key_left || game->player.key_right))
	{
		game->bar.time = current_time();
		i += dir;
	
		if (i >= 4)
		{
			i = 3;
			dir = -1;
		}
		else if (i <= 1)
		{
			i = 1;
			dir = 1;
		}
	}
	else if (current_time() - game->bar.time > 200)
		i = 1;
	mlx_get_image_region(game->mlx, game->bar.bar, 140 * i, 0,  135, 271, tmp);			// cut 1st sprite
	put_region_to_array(game->frame_buffer, (vec2){WIDTH - 135, HEIGHT - 271}, (vec2){135, 271}, tmp);
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
	if (game->bar.valid)
		draw_crow(game);
	mlx_pixel_put_region(game->mlx, game->win, 0, 0, WIDTH, HEIGHT, game->frame_buffer);
}