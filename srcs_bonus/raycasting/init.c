/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 05:42:03 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	init_frame_buffer(t_game *game)
{
	game->frame_buffer = malloc(sizeof(mlx_color) * WIDTH * HEIGHT);
	if (!game->frame_buffer)
	{
		ft_printf(2, "Error: Failed to allocate frame buffer\n");
		cleanup_game(game);
		exit(1);
	}
}

static void	handle_image_error(t_game *game, int type)
{
	if (type == 0)
		ft_printf(2, "Error: failed to load crowbar image\n");
	else
		ft_printf(2, "Error: failed to load kunai image %d\n", type);
	game->bar.valid[type] = 0;
}

static void	copy_pixel_data(t_game *game, int type, int x, int y)
{
	mlx_color	*pixel;

	pixel = &game->bar.c[game->bar.type][x * game->bar.y[type] + y];
	if (type == 0)
		*pixel = mlx_get_image_pixel(game->mlx, game->bar.item[type], y, x);
}

static void	process_image_pixels(t_game *game, int type, int width, int height)
{
	int	x;
	int	y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < width)
		{
			copy_pixel_data(game, type, x, y);
			y++;
		}
		x++;
	}
}

void	fill_item(t_game *game, char path[50], int type)
{
	int	width;
	int	height;

	game->bar.item[type] = mlx_new_image_from_file(game->mlx,
			path, &height, &width);
	if (!game->bar.item[type])
	{
		handle_image_error(game, type);
		return ;
	}
	process_image_pixels(game, type, width, height);
	game->bar.time[type] = current_time();
}
