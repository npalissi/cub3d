/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:30:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 02:55:25 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	init_fps(t_game *game)
{
	game->fps_data.last_time = current_time();
	game->fps_data.current_time = 0;
	game->fps_data.frame_count = 0;
	game->fps_data.fps = 0;
	game->fps_data.fps_timer = 0;
}

void	update_fps(t_game *game)
{
	game->fps_data.current_time = current_time();
	game->fps_data.frame_count++;
	if (game->fps_data.current_time - game->fps_data.fps_timer >= 1000)
	{
		game->fps_data.fps = game->fps_data.frame_count;
		game->fps_data.frame_count = 0;
		game->fps_data.fps_timer = game->fps_data.current_time;
	}
}

void	fill_str(char *str, int i)
{
	str[i++] = ' ';
	str[i++] = 'F';
	str[i++] = 'P';
	str[i++] = 'S';
	str[i] = '\0';
}

void	draw_fps(t_game *game)
{
	char				fps_str[20];
	int					i[2];
	int					fps_temp;
	char				temp[20];
	static mlx_color	white = {{255, 255, 255, 255}};

	i[0] = 0;
	fps_temp = game->fps_data.fps;
	if (fps_temp == 0)
		fps_str[i[0]++] = '0';
	else
	{
		i[1] = 0;
		while (fps_temp > 0)
		{
			temp[i[1]++] = (fps_temp % 10) + '0';
			fps_temp /= 10;
		}
		while (i[1] > 0)
			fps_str[i[0]++] = temp[--i[1]];
	}
	fill_str(fps_str, i[0]);
	mlx_string_put(game->mlx, game->win, 10, 20, white, fps_str);
}
