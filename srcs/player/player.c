/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:52:45 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/24 15:19:46 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

void	init_player(t_player *player)
{
	player->x = 5 * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->y = 5 * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->angle = 0;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	key_press(int keycode, void *params)
{
	t_game	*game;

	game = params;
	if (keycode == TAB)
		game->mini.down = true;
	if (keycode == W)
		game->player.key_up = true;
	if (keycode == S)
		game->player.key_down = true;
	if (keycode == A)
		game->player.key_left = true;
	if (keycode == D)
		game->player.key_right = true;
	if (keycode == LEFT)
		game->player.left_rotate = true;
	if (keycode == RIGHT)
		game->player.right_rotate = true;
	if (keycode == ESC)
		mlx_loop_end(game->mlx);
}

void	key_release(int keycode, void *params)
{
	t_game	*game;

	game = params;
	if (keycode == TAB)
		game->mini.down  = false;
	if (keycode == W)
		game->player.key_up = false;
	if (keycode == S)
		game->player.key_down = false;
	if (keycode == A)
		game->player.key_left = false;
	if (keycode == D)
		game->player.key_right = false;
	if (keycode == LEFT)
		game->player.left_rotate = false;
	if (keycode == RIGHT)
		game->player.right_rotate = false;
}

void	mouse_up(int button, void *params)
{
	t_game	*game;

	game = params;
	if (button == 1)
		game->mouse.is_press = false;
}

void	mouse_down(int button, void *params)
{
	t_game	*game;

	game = params;
	if (button == 1)
	{
		game->mouse.is_press = true;
		mlx_mouse_get_pos(game->mlx, &game->mouse.x, &game->mouse.y);
	}
}
