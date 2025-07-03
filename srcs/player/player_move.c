/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/02 22:17:20 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

static void	handle_rotation(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.03;
	if (player->left_rotate)
	{
		player->angle -= angle_speed;
		update_angle(player);
	}
	if (player->right_rotate)
	{
		player->angle += angle_speed;
		update_angle(player);
	}
}


static void	handle_movement(t_player *player, t_game *game)
{
	int		speed;
	float	cos_angle;
	float	sin_angle;
	
	
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	speed = 3;
	if (player->key_up)
	update_move_player(cos_angle * speed, sin_angle * speed, game);
	if (player->key_down)
	update_move_player(-cos_angle * speed, -sin_angle * speed, game);
	if (player->key_left)
	update_move_player(sin_angle * speed, -cos_angle * speed, game);
	if (player->key_right)
	update_move_player(-sin_angle * speed, cos_angle * speed, game);
}


void	move_player(t_player *player, t_game *game)
{
	handle_rotation(player);
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;

	handle_movement(player, game);
}