/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/02 22:06:18 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

// Fonctions de sprite rendering pour ttranche


typedef struct 
{
	uint32_t x;
	uint32_t y;
}	vec2;

void put_region_to_array(mlx_color *fb, vec2 start, vec2 size, mlx_color *src)
{
	for (uint32_t y = 0; y < size.y; ++y)
	{
		for (uint32_t x = 0; x < size.x; ++x)
		{
			uint32_t sindex = y * size.x + x; // source = tmp[y][x]
			uint32_t index = (start.y + y) * WIDTH + (start.x + x); // dest = fb[y+start.y][x+start.x]

			if (!src[sindex].a)
				continue;
			fb[index] = src[sindex];
		}
	}
}

void	draw_crow(t_game *game)
{
	static mlx_color	tmp[WIDTH * HEIGHT] = {0};

	static int i = 1;
	static int dir = 1; // 1 = forward, -1 = backward
	
	if (current_time() - game->bar.time[0] > 200 && (game->player.key_up ||game->player.key_down|| game->player.key_left || game->player.key_right))
	{
		game->bar.time[0] = current_time();
		i += dir;
	
		if (i >= 4)
		{
			i = 3;
			dir = -1;
		}
		else if (i <= 1)
		{
			i = 1;
			dir = 1;
		}
	}
	else if (current_time() - game->bar.time[0] > 200)
		i = 1;
	mlx_get_image_region(game->mlx, game->bar.item[0], 140 * i, 0,  135, 271, tmp);			// cut 1st sprite
	put_region_to_array(game->frame_buffer, (vec2){WIDTH - 135, HEIGHT - 271}, (vec2){135, 271}, tmp);
}

void	draw_exit_kunai(t_game *game, bool *done)
{
	static mlx_color	tmp[WIDTH * HEIGHT] = {0};

	static int i = 0;
	if (current_time() - game->bar.time[game->bar.type] > game->bar.wait[game->bar.type] && (game->player.key_up ||game->player.key_down|| game->player.key_left || game->player.key_right))
	{
		game->bar.time[1] = current_time();
	
		if (i > 69)
		{
			i = 0;
			*done = true;
		}
		i++;
	}
	else if (current_time() - game->bar.time[1] > game->bar.wait[game->bar.type])
		i = 69;
	mlx_get_image_region(game->mlx, game->bar.item[1], 1920 * i, 0,  1920, 1080, tmp);			// cut 1st sprite
	put_region_to_array(game->frame_buffer, (vec2){0, 0}, (vec2){1920, 1080}, tmp);
}

void	draw_transition(t_game *game, bool *done)
{
	static mlx_color	tmp[WIDTH * HEIGHT] = {0};

	static int i = 0;
	if (current_time() - game->bar.time[game->bar.type] > game->bar.wait[game->bar.type] && (game->player.key_up ||game->player.key_down|| game->player.key_left || game->player.key_right))
	{
		game->bar.time[1] = current_time();
	
		i++;
	}
	mlx_get_image_region(game->mlx, game->bar.item[3], 1920 * i, 0,  1920, 1080, tmp);			// cut 1st sprite
	put_region_to_array(game->frame_buffer, (vec2){0, 0}, (vec2){1920, 1080}, tmp);
	if (i > 18)
	{
		i = 0;
		*done = true;
	}
}

void	draw_sprinting_kunai(t_game *game, bool is_moving)
{
	static mlx_color	tmp[WIDTH * HEIGHT] = {0};
	static int i = 0;

	if (current_time() - game->bar.time[game->bar.type] > game->bar.wait[game->bar.type] && is_moving)
	{
		game->bar.time[1] = current_time();
		if (i > 24)
			i = 0;
		i++;
	}
	else if (current_time() - game->bar.time[1] > game->bar.wait[game->bar.type])
		i = 0;
	mlx_get_image_region(game->mlx, game->bar.item[2], 1920 * i, 0,  1920, 1080, tmp);			// cut 1st sprite
	put_region_to_array(game->frame_buffer, (vec2){0, 0}, (vec2){1920, 1080}, tmp);
}


// render_frame() moved to render.c

