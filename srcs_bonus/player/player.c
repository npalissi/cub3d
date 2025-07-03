/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:52:45 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 13:09:00 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

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

int	manage_index(t_game *game, int index)
{
	if (index == -1)
		ft_printf(2, "You need to be near a door to open it !\n");
	if (!game->bar.wheel && index != -1)
		ft_printf(2, "Take crowbar to open/close door !\n");
	if (!game->bar.wheel)
		index = -1;
	return (index);
}

int	nearest_door(t_game *game)
{
	int		i;
	int		nearest_index;
	int		dist[2];
	t_vec2	pvec;
	t_vec2	dvec;

	pvec.x = (int)(game->player.x / BLOCK_SIZE);
	pvec.y = (int)(game->player.y / BLOCK_SIZE);
	i = 0;
	dist[0] = 999999;
	nearest_index = -1;
	while (game->d[i].x)
	{
		dvec.x = ft_abs(game->d[i].x - pvec.x);
		dvec.y = ft_abs(game->d[i].y - pvec.y);
		dist[1] = dvec.x + dvec.y;
		if (dist[1] <= 2 && dist[1] < dist[0])
		{
			dist[0] = dist[1];
			nearest_index = i;
		}
		i++;
	}
	return (manage_index(game, nearest_index));
}

void	check_all(int keycode, t_game *game)
{
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
