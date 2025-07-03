/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:08:10 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 13:09:03 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	key_press(int keycode, void *params)
{
	t_game	*game;
	int		index;

	game = params;
	if (keycode == F)
	{
		index = nearest_door(game);
		if (index != -1 && (((int)game->player.x
					/ BLOCK_SIZE != game->d[index].x)
				|| ((int)game->player.y / BLOCK_SIZE != game->d[index].y)))
			game->d[index].pressed = !game->d[index].pressed;
		else if (index != -1)
			printf("You must be out of the way to close a door !\n");
	}
	if (keycode == TAB)
		game->mini.down = true;
	if (keycode == W)
		game->player.key_up = true;
	if (keycode == S)
		game->player.key_down = true;
	check_all(keycode, game);
}

void	key_release(int keycode, void *params)
{
	t_game	*game;

	game = params;
	if (keycode == TAB)
		game->mini.down = false;
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

void	mouse_wheel(int keycode, void *params)
{
	static int	first;
	static int	scroll_count;
	t_game		*game;

	(void)keycode;
	game = params;
	scroll_count++;
	if (scroll_count > 8)
	{
		if (!first)
			game->bar.wheel = true;
		first++;
		if (game->bar.wheel)
			game->bar.wheel = false;
		else
			game->bar.wheel = true;
		scroll_count = 0;
	}
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
