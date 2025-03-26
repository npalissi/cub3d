/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:15:17 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/26 00:47:15 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void draw_squar(t_game *game, int x, int y, int size)
{
	int i;

	i = 0;
	while(i < size)
		mlx_pixel_put(game->mlx, game->win, x + i++, y, (mlx_color){.rgba = 0xFF0000FF});
	i = 0;
	while(i < size)
		mlx_pixel_put(game->mlx, game->win, x + i++, y + size, (mlx_color){.rgba = 0xFF00F0FF});
	i = 0;
	while(i < size)
	{
		mlx_pixel_put(game->mlx, game->win, x, y + i, (mlx_color){.rgba = 0xFF0000FF});
		mlx_pixel_put(game->mlx, game->win, x + size, y + i, (mlx_color){.rgba = 0xFF0000FF});
		i++;
	}
}