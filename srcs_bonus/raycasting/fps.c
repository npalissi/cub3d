/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:30:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/02 22:06:18 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void init_fps(t_game *game)
{
	game->fps_data.last_time = current_time();
	game->fps_data.current_time = 0;
	game->fps_data.frame_count = 0;
	game->fps_data.fps = 0;
	game->fps_data.fps_timer = 0;
}

void update_fps(t_game *game)
{
	game->fps_data.current_time = current_time();
	game->fps_data.frame_count++;
	
	// Calculer FPS chaque seconde (1000 ms)
	if (game->fps_data.current_time - game->fps_data.fps_timer >= 1000)
	{
		game->fps_data.fps = game->fps_data.frame_count;
		game->fps_data.frame_count = 0;
		game->fps_data.fps_timer = game->fps_data.current_time;
	}
}

void draw_fps(t_game *game)
{
	char fps_str[20];
	int i = 0;
	int fps_temp = game->fps_data.fps;
	
	// Convertir FPS en string
	if (fps_temp == 0)
	{
		fps_str[i++] = '0';
	}
	else
	{
		char temp[20];
		int j = 0;
		
		while (fps_temp > 0)
		{
			temp[j++] = (fps_temp % 10) + '0';
			fps_temp /= 10;
		}
		
		while (j > 0)
		{
			fps_str[i++] = temp[--j];
		}
	}
	
	// Ajouter " FPS"
	fps_str[i++] = ' ';
	fps_str[i++] = 'F';
	fps_str[i++] = 'P';
	fps_str[i++] = 'S';
	fps_str[i] = '\0';
	
	// Afficher le texte FPS en haut à gauche
	mlx_color white = {{255, 255, 255, 255}};
	mlx_string_put(game->mlx, game->win, 10, 20, white, fps_str);
}