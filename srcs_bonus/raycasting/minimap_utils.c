/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:43:53 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 12:44:18 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

int	get_max_map_width(char **map)
{
	int	max;
	int	i;
	int	len;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

t_minimap_config	get_minimap_config(t_game *game)
{
	t_minimap_config	config;

	config.map_size.y = ft_arraylen(game->mini.map);
	config.map_size.x = get_max_map_width(game->mini.map);
	config.minimap_size.x = config.map_size.x * TILE_SIZE;
	config.minimap_size.y = config.map_size.y * TILE_SIZE;
	config.offset.x = (WIDTH - config.minimap_size.x) / 2;
	config.offset.y = (HEIGHT - config.minimap_size.y) / 2;
	return (config);
}
