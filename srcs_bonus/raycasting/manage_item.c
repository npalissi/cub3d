/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_item.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:41:38 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 05:43:05 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	handle_file_error(t_game *game, int type)
{
	if (type == 0)
		ft_printf(2, "Textures for crowbar have been modified,"
			" starting without crowbar !\n");
	else
		ft_printf(2, "Textures for kunai have been modified,"
			" starting without kunai %d!\n", type);
	game->bar.valid[type] = 0;
}

void	set_item_dimensions(t_game *game)
{
	game->bar.x[0] = 651;
	game->bar.x[1] = 134400;
	game->bar.x[2] = 46080;
	game->bar.x[3] = 46080;
	game->bar.y[0] = 271;
	game->bar.y[1] = 1080;
	game->bar.y[2] = 1080;
	game->bar.y[3] = 1080;
}

bool	check_window_size(t_game *game, int type)
{
	if (type == 0)
	{
		if (HEIGHT < 271 || WIDTH < 140)
		{
			ft_printf(2, "Error, windows is to tight to put item,"
				" starting without crowbar\n");
			game->bar.valid[type] = 0;
			return (false);
		}
	}
	else
	{
		if (HEIGHT < 1080 || WIDTH < 1920)
		{
			ft_printf(2, "Error, windows is to tight to put item,"
				" starting without kunai %d\n", type);
			game->bar.valid[type] = 0;
			return (false);
		}
	}
	return (true);
}

void	allocate_item_memory(t_game *game, int type)
{
	uint64_t	size;

	size = game->bar.x[type] * game->bar.y[type] * sizeof(mlx_color);
	game->bar.size[type] = size;
	game->bar.c[type] = (mlx_color *)mmap(NULL, size, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
}

void	set_wait_time(t_game *game, int type)
{
	game->bar.wait[type] = 30;
	if (type == 0)
		game->bar.wait[type] = 200;
}
