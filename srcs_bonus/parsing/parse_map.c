/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:59:48 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 02:35:06 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	fill_map(char **map, int i)
{
	int	j;
	int	lm;

	lm = len_max(map) - 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (ft_iswhitespace(map[i][j]))
				map[i][j] = '0';
			j++;
		}
		if (map[i][j] == '\n' || !map[i + 1])
		{
			map[i] = ft_substr(map[i], 0, j);
			while (j++ <= lm)
				map[i] = ft_strjoinfree(map[i], "0", 1);
			map[i] = ft_strjoinfree(map[i], "\n", 1);
		}
		i++;
	}
}

int	parse_map(char **map, t_game *game)
{
	int		i;
	char	**save_map;

	i = 0;
	while (map[i] && !first_char(map[i], '1'))
		i++;
	game->mini.skipped = i - 2;
	if (!map[i])
	{
		ft_printf(2, "Error, Need map in config file !\n");
		return (0);
	}
	game->mini.map = ft_arraydupe(map + i);
	fill_map(map, i);
	save_map = ft_arraydupe(map);
	if (!flood_fill(save_map, find_y(save_map, i), find_x(save_map, i),
			ft_arraylen(save_map)))
	{
		ft_free_tab(save_map);
		ft_printf(2, "Error, The map needs to be closed !\n");
		return (0);
	}
	ft_free_tab(save_map);
	return (1);
}

void	check_map(char *map, int *error)
{
	int	j;

	j = 0;
	while (map[j])
	{
		if (!ft_strchr("10NSWE\n", map[j]))
		{
			ft_printf(2, "Error, "RED"%c"RESET
				" must not be inside of the map !\n", map[j]);
			*error = 0;
		}
		j++;
	}
}

int	fill_stat(t_game *game, int stat[4], int *error)
{
	int	i;

	i = 0;
	while (game->map.map[i])
	{
		get_door(game, i);
		check_map(game->map.map[i], error);
		stat[0] += ft_charite(game->map.map[i], 'N');
		stat[1] += ft_charite(game->map.map[i], 'S');
		stat[2] += ft_charite(game->map.map[i], 'E');
		stat[3] += ft_charite(game->map.map[i], 'W');
		i++;
	}
	return (i);
}

int	cut_map(t_game *game)
{
	static int	stat[4] = {0, 0, 0, 0};
	int			i;
	int			error;

	error = 1;
	while (*game->map.map && (!first_char(*game->map.map, '1')
			&& !(first_char(*game->map.map, '0'))))
		game->map.map++;
	game->d = ft_calloc(sizeof(t_door),
			(ft_arrayoccu(game->map.map, 'D') + 1));
	if (!game->d)
		return (error);
	game->d->pressed = false;
	i = fill_stat(game, stat, &error);
	if ((stat[0] + stat[1] + stat[2] + stat[3]) != 1)
	{
		ft_printf(2, "Error, player spawnpoint must be declared only"
			" once and not %d times!\n", stat[0] + stat[1] + stat[2] + stat[3]);
		return (0);
	}
	game->map.h = i;
	game->map.w = len_max(game->map.map);
	return (error);
}
