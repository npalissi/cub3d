/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:15:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/02 23:23:59 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

void	cleanup_game(t_game *game)
{
	if (game->color.cl)
		dh_free(game->color.cl);
	if (game->color.cl)
		dh_free(game->color.cl);
	ft_free_tab(game->map.full_map);
	if (game->frame_buffer)
		free(game->frame_buffer);
	if (game->texture.north_img)
		mlx_destroy_image(game->mlx, game->texture.north_img);
	if (game->texture.south_img)
		mlx_destroy_image(game->mlx, game->texture.south_img);
	if (game->texture.west_img)
		mlx_destroy_image(game->mlx, game->texture.west_img);
	if (game->texture.east_img)
		mlx_destroy_image(game->mlx, game->texture.east_img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_context(game->mlx);
}
