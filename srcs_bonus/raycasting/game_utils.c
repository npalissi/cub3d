/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 03:13:13 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 12:05:44 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	init_player_position(t_game *game, int x, int y)
{
	game->player.x = x * BLOCK_SIZE + BLOCK_SIZE / 2;
	game->player.y = y * BLOCK_SIZE + BLOCK_SIZE / 2;
}

void	set_player_angle(t_game *game, char dir)
{
	if (dir == 'N')
		game->player.angle = 3 * PI / 2;
	else if (dir == 'S')
		game->player.angle = PI / 2;
	else if (dir == 'E')
		game->player.angle = 0;
	else if (dir == 'W')
		game->player.angle = PI;
}

void	load_map_data(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.h && game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x] && game->map.map[y][x] != '\n')
		{
			if (game->map.map[y][x] == 'N' || game->map.map[y][x] == 'S'
				|| game->map.map[y][x] == 'E' || game->map.map[y][x] == 'W')
			{
				init_player_position(game, x, y);
				set_player_angle(game, game->map.map[y][x]);
				game->map.map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

static int	load_texture(t_game *game,
	char *path, struct mlx_image_handler **img)
{
	int	width;
	int	height;

	*img = mlx_new_image_from_file(game->mlx, path, &width, &height);
	game->texture.width = width;
	game->texture.height = height;
	if (!*img)
	{
		ft_printf(2, "Error: Could not load texture: %s\n", path);
		return (0);
	}
	return (1);
}

int	load_textures(t_game *game)
{
	if (!load_texture(game, game->texture.north, &game->texture.north_img))
		return (0);
	if (!load_texture(game, game->texture.south, &game->texture.south_img))
		return (0);
	if (!load_texture(game, game->texture.west, &game->texture.west_img))
		return (0);
	if (!load_texture(game, game->texture.east, &game->texture.east_img))
		return (0);
	if (game->texture.door)
	{
		if (!load_texture(game, game->texture.door, &game->texture.door_img))
			return (0);
	}
	else
		game->texture.door_img = NULL;
	return (1);
}
