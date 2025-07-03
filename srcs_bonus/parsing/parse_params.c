/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:17:04 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 02:35:18 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	get_door(t_game *game, int y)
{
	static int	idx;
	int			x;

	x = 0;
	while (game->map.map[y][x])
	{
		if (game->map.map[y][x] == 'D')
		{
			game->map.map[y][x] = '1';
			game->d[idx].x = x;
			game->d[idx++].y = y;
		}
		x++;
	}
}

int	parse_occu(char **map)
{
	static char		*key_mapping[7] = {"NO", "SO", "EA", "WE", "F", "C", "DO"};
	int				i;
	int				error;

	i = 0;
	error = 1;
	while (i < 7)
	{
		if (count_occurrences(key_mapping[i], map) != 1)
			error = 0;
		i++;
	}
	return (error);
}
