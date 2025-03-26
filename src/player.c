/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:52:45 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/26 02:16:38 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}


void key_press(int keycode, void *params)
{
	t_game *game;

	game = params;	
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
	// printf("keycode %d\n", keycode);
}

void key_release(int keycode, void *params)
{
	t_game *game;

	game = params;	
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
	printf("keycode %d\n", keycode);	
}

void mouse_up(int button, void *params)
{
	t_game *game;

	game = params;
	if (button == 1)
		game->mouse.is_press = false;
	printf("button %d\n", button);
}

void mouse_down(int button, void *params)
{
	t_game *game;
	game = params;
	if (button == 1)
	{
		game->mouse.is_press = true;
		mlx_mouse_get_pos(game->mlx, &game->mouse.x, &game->mouse.y);
	}
		

}


void pos_mouse(t_game *game)
{
	int x;
	int y;

	mlx_mouse_get_pos(game->mlx, &x, &y);
	printf("x %d y %d\n", x, y);

}

void move_player(t_player *player, t_game *game)
{
	int speed;
	float angle_speed;
	float cos_angle;
	float sin_angle;
	int x;
	int y;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	angle_speed = 0.03;
	speed = 3;

	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;

	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key_up)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	if (player->key_right)
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
	if (game->mouse.is_press)
	{
		mlx_mouse_get_pos(game->mlx, &x, &y);
		player->angle -= angle_speed * ((speed * ((x - game->mouse.x) / 10)));
		game->mouse.x = x;
	}
}