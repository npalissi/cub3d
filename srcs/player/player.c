/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:52:45 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/02 19:33:20 by npalissi         ###   ########.fr       */
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

int nearest_door(t_game *game)
{
    int i = 0;
    int nearest_index = -1;
    int min_dist = 999999; // valeur très grande

    int px = (int)(game->player.x / BLOCK_SIZE);
    int py = (int)(game->player.y / BLOCK_SIZE);

    while (game->d[i].x)
    {
        int dx = ft_abs(game->d[i].x - px);
        int dy = ft_abs(game->d[i].y - py);
        int dist = dx + dy;

        if (dist <= 2 && dist < min_dist)
        {
            min_dist = dist;
            nearest_index = i;
        }
        i++;
    }
	if (nearest_index == -1)
		ft_printf(2, "You need to be near a door to open it !\n");
	if (!game->bar.wheel && nearest_index != -1)
		ft_printf(2, "Take crowbar to open/close door !\n");
	if (!game->bar.wheel)
		nearest_index = -1;
    return nearest_index; // -1 si aucune porte dans la portée
}



void	key_press(int keycode, void *params)
{
	t_game	*game;
	int		index;

	game = params;
	if (keycode == F)
    {
        index = nearest_door(game);
        if (index != -1 && (((int)game->player.x / BLOCK_SIZE != game->d[index].x) || ((int)game->player.y / BLOCK_SIZE != game->d[index].y)))
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

void	mouse_wheel(int keycode, void *params)
{
	static int first;
	static int scroll_count;
	t_game	*game;

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
