/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 13:10:42 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	pos_mouse(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx, &x, &y);
}

void	update_move_player(float x, float y, t_game *game)
{
	float	new_pos_x;
	float	new_pos_y;
	int		grid_x;
	int		grid_y;

	new_pos_x = game->player.x + x;
	new_pos_y = game->player.y + y;
	grid_x = (int)(new_pos_x / BLOCK_SIZE);
	grid_y = (int)(new_pos_y / BLOCK_SIZE);
	if (grid_x >= 0 && grid_x < game->map.w
		&& grid_y >= 0 && grid_y < game->map.h
		&& game->map.map[grid_y][grid_x] == '0')
	{
		game->player.x = new_pos_x;
		game->player.y = new_pos_y;
	}
}

void	update_angle(t_player *player)
{
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
}
