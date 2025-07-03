/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:39:25 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 05:40:59 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	init_pixel(t_game *game)
{
	int	y;
	int	x;

	game->mini.c = malloc(sizeof(mlx_color) * 25 * 25);
	if (!game->mini.c)
	{
		ft_printf(2, "Error failled allocation for character pixel\n");
		return ;
	}
	y = 0;
	while (y != 25)
	{
		x = 0;
		while (x != 25)
		{
			game->mini.c[y * 25 + x] = mlx_get_image_pixel(game->mlx,
					game->mini.character, x, y);
			x++;
		}
		y++;
	}
}

void	init_item(t_game *game, char path[50], int type)
{
	int	fd;

	fd = open(path, O_RDONLY);
	game->bar.valid[type] = 1;
	if (fd == -1)
	{
		handle_file_error(game, type);
		return ;
	}
	set_item_dimensions(game);
	if (!check_window_size(game, type))
	{
		close(fd);
		return ;
	}
	allocate_item_memory(game, type);
	if (game->bar.c[type] == MAP_FAILED)
	{
		close(fd);
		return ;
	}
	fill_item(game, path, type);
	close(fd);
	set_wait_time(game, type);
	game->bar.type = type;
}

void	make_minimap(t_game *game, char wall[50],
	char background[50], char character[50])
{
	static int	w = 25;

	ft_array_replace(game->mini.map, "NSWE", '0');
	game->mini.wall = mlx_new_image_from_file(game->mlx, wall, &w, &w);
	game->mini.back = mlx_new_image_from_file(game->mlx, background, &w, &w);
	game->mini.character = mlx_new_image_from_file(game->mlx,
			character, &w, &w);
	if (!game->mini.wall || !game->mini.back || !game->mini.character)
	{
		ft_printf(2, "Error, could not load minimap texture,"
			"starting without minimap\n");
		game->mini.valid = 0;
	}
	init_pixel(game);
}

void	init_minimap(t_game *game)
{
	static char	wall[50] = "minimap_textures/half_wall.png";
	static char	background[50] = "minimap_textures/half_background.png";
	static char	character[50] = "minimap_textures/character.png";
	int			fd[3];

	game->mini.valid = 1;
	fd[0] = open(wall, O_RDONLY);
	fd[1] = open(background, O_RDONLY);
	fd[2] = open(character, O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1)
	{
		ft_printf(2, "Textures for minimap have been modified,"
			" starting without minimap !\n");
		game->mini.valid = 0;
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);
		make_minimap(game, wall, background, character);
	}
}
