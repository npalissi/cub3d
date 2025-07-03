/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:10:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 03:13:11 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	init_game(t_game *game)
{
	game->mouse.x = 0;
	game->mouse.y = 0;
	game->mouse.is_press = 0;
	game->lst_buffer = NULL;
	init_fps(game);
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

void	manage_door(t_game *game)
{
	int	i;

	i = 0;
	while (game->d[i].x)
	{
		if (game->d[i].pressed && game->bar.wheel)
		{
			game->map.map[game->d[i].y][game->d[i].x] = '0';
			game->mini.map[game->d[i].y][game->d[i].x] = '0';
		}
		else if (!game->d[i].pressed)
		{
			game->map.map[game->d[i].y][game->d[i].x] = '1';
			game->mini.map[game->d[i].y][game->d[i].x] = '1';
		}
		i++;
	}
}

void	draw_loop(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	move_player(&game->player, game);
	update_fps(game);
	mlx_clear_window(game->mlx, game->win, (mlx_color){{255, 0, 0, 0}});
	manage_door(game);
	render_frame(game);
	if (game->mini.valid && game->mini.down)
		draw_minimap(game);
	draw_fps(game);
}

bool	touch(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / BLOCK_SIZE);
	map_y = (int)(y / BLOCK_SIZE);
	if (map_x < 0 || map_x >= game->map.w
		|| map_y < 0 || map_y >= game->map.h)
		return (true);
	return (game->map.map[map_y][map_x] == WALL);
}
