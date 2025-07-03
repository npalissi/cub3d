/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:14:18 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/02 23:48:33 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	fill_color(t_game *game, int i)
{
	int	overflow;
	int	size;

	size = ft_strlen(*game->map.map);
	overflow = 0;
	if (i == 1)
	{
		game->color.floor = rgba_to_hex(ft_substr(*game->map.map, 2,
					size - 3), &overflow);
		game->color.fl = ft_substr(*game->map.map, 0, size);
	}
	else
	{
		game->color.ceiling = rgba_to_hex(ft_substr(*game->map.map, 2,
					size - 3), &overflow);
		game->color.cl = ft_substr(*game->map.map, 0, size);
	}
	if (overflow == 1)
		ft_printf(2, "Error, color have to be between 0 and 255 for rgb !\n");
	if (ft_charite(*game->map.map, ',') != 2 || overflow == 2)
	{
		ft_printf(2, "Error, color have to be under rgb type (R,G,B)\n");
		overflow = 1;
	}
	return (overflow != 1);
}

void	init_co(char *(*co)[2], int *i, char ***save_map, t_game *game)
{
	(*co)[0] = "C ";
	(*co)[1] = "F ";
	*i = 0;
	*save_map = game->map.map;
}

int	get_colors(t_game *game)
{
	char	**save_map;
	char	*co[2];
	int		i;

	init_co(&co, &i, &save_map, game);
	while (i < 2)
	{
		game->map.map = save_map;
		while (!ft_strcmp(ft_substr(*game->map.map, 0, 2), co[i])
			&& *game->map.map)
			game->map.map++;
		if (*game->map.map)
		{
			if (!fill_color(game, i))
				return (0);
			i++;
		}
		else
		{
			ft_printf(2, "Error, Not all color codes are there\
				 ! Missing at least: %s\n", co[i]);
			return (0);
		}
	}
	return (1);
}
