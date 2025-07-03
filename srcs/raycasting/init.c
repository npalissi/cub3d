/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 00:30:16 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

void	init_frame_buffer(t_game *game)
{
	game->frame_buffer = malloc(sizeof(mlx_color) * WIDTH * HEIGHT);
	if (!game->frame_buffer)
	{
		ft_printf(2, "Error: Failed to allocate frame buffer\n");
		cleanup_game(game);
		exit(1);
	}
}
