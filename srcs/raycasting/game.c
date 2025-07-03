/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:10:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 00:27:11 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

void	init_game(t_game *game)
{
	game->lst_buffer = NULL;
}

void	close_win(int event, void *params)
{
	t_game	*game;

	game = (t_game *)params;
	if (event == 0)
		mlx_loop_end(game->mlx);
}

void	draw_loop(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	move_player(&game->player, game);
	mlx_clear_window(game->mlx, game->win, (mlx_color){{255, 0, 0, 0}});
	render_frame(game);
}

static void	set_player_position(t_game *game, int x, int y, char direction)
{
	game->player.x = x * BLOCK_SIZE + BLOCK_SIZE / 2;
	game->player.y = y * BLOCK_SIZE + BLOCK_SIZE / 2;
	if (direction == 'N')
		game->player.angle = 3 * PI / 2;
	else if (direction == 'S')
		game->player.angle = PI / 2;
	else if (direction == 'E')
		game->player.angle = 0;
	else if (direction == 'W')
		game->player.angle = PI;
	game->map.map[y][x] = '0';
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
				set_player_position(game, x, y, game->map.map[y][x]);
			x++;
		}
		y++;
	}
}
