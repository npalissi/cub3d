/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:10:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/26 17:42:26 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

void	init_game(t_game *game)
{
	game->mouse.x = 0;
	game->mouse.y = 0;
	game->mouse.is_press = 0;
	game->lst_buffer = NULL;
}

void	close_win(int event, void *params)
{
	t_game	*game;

	game = (t_game *)params;
	if (event == 0)
	{
		mlx_loop_end(game->mlx);
	}
}



void	draw_loop(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	move_player(&game->player, game);
	
	// Effacer la fenêtre avant de redessiner
	mlx_clear_window(game->mlx, game->win, (mlx_color){{255, 0, 0, 0}});
	

	render_frame(game);
	if (game->mini.valid && game->mini.down)
		draw_minimap(game);
}

bool	touch(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / BLOCK_SIZE);
	map_y = (int)(y / BLOCK_SIZE);
	if (map_x < 0 || map_x >= game->map.w || 
		map_y < 0 || map_y >= game->map.h)
		return (true);
	return (game->map.map[map_y][map_x] == WALL);
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
			if (game->map.map[y][x] == 'N' || game->map.map[y][x] == 'S' ||
				game->map.map[y][x] == 'E' || game->map.map[y][x] == 'W')
			{
				game->player.x = x * BLOCK_SIZE + BLOCK_SIZE / 2;
				game->player.y = y * BLOCK_SIZE + BLOCK_SIZE / 2;
				if (game->map.map[y][x] == 'N')
					game->player.angle = 3 * PI / 2;
				else if (game->map.map[y][x] == 'S')
					game->player.angle = PI / 2;
				else if (game->map.map[y][x] == 'E')
					game->player.angle = 0;
				else if (game->map.map[y][x] == 'W')
					game->player.angle = PI;
				game->map.map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

int	load_textures(t_game *game)
{
	int width, height;
	
	game->texture.north_img = mlx_new_image_from_file(game->mlx, game->texture.north, &width, &height);
	if (!game->texture.north_img)
	{
		ft_printf(2, "Error: Could not load north texture: %s\n", game->texture.north);
		return (0);
	}
	game->texture.width = width;
	game->texture.height = height;
	
	game->texture.south_img = mlx_new_image_from_file(game->mlx, game->texture.south, &width, &height);
	if (!game->texture.south_img)
	{
		ft_printf(2, "Error: Could not load south texture: %s\n", game->texture.south);
		return (0);
	}
	
	game->texture.west_img = mlx_new_image_from_file(game->mlx, game->texture.west, &width, &height);
	if (!game->texture.west_img)
	{
		ft_printf(2, "Error: Could not load west texture: %s\n", game->texture.west);
		return (0);
	}
	
	game->texture.east_img = mlx_new_image_from_file(game->mlx, game->texture.east, &width, &height);
	if (!game->texture.east_img)
	{
		ft_printf(2, "Error: Could not load east texture: %s\n", game->texture.east);
		return (0);
	}
	
	return (1);
}
