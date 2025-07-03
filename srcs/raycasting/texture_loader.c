/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:30:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 01:32:49 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

static int	load_single_texture(t_game *game, char *path, mlx_image *img_ptr,
	char *direction)
{
	int	width;
	int	height;

	*img_ptr = mlx_new_image_from_file(game->mlx, path, &width, &height);
	if (!*img_ptr)
	{
		ft_printf(2, "Error: Could not load %s texture: %s\n",
			direction, path);
		return (0);
	}
	if (game->texture.width == 0)
	{
		game->texture.width = width;
		game->texture.height = height;
	}
	return (1);
}

int	load_textures(t_game *game)
{
	if (!load_single_texture(game, game->texture.north,
			&game->texture.north_img, "north"))
		return (0);
	if (!load_single_texture(game, game->texture.south,
			&game->texture.south_img, "south"))
		return (0);
	if (!load_single_texture(game, game->texture.west,
			&game->texture.west_img, "west"))
		return (0);
	if (!load_single_texture(game, game->texture.east,
			&game->texture.east_img, "east"))
		return (0);
	return (1);
}
