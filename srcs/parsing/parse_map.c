/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:15:04 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 03:21:22 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int	is_in_bounds(char **map, int x, int y, int height)
{
	int	row_len;

	if (y < 0 || y >= height)
		return (0);
	if (!map[y])
		return (0);
	row_len = ft_strlen(map[y]);
	if (x < 0 || x >= row_len)
		return (0);
	return (1);
}

int	flood_fill(char **map, int x, int y, int height)
{
	int	right;
	int	left ;
	int	down ;
	int	up;

	if (!is_in_bounds(map, x, y, height))
		return (0);
	if (map[y][x] != EMPTY && map[y][x] != 'N' && map[y][x] != 'S'
		&& map[y][x] != 'E' && map[y][x] != 'W' && map[y][x] != 'D')
		return (1);
	map[y][x] = VISITED;
	right = flood_fill(map, x + 1, y, height);
	left = flood_fill(map, x - 1, y, height);
	down = flood_fill(map, x, y + 1, height);
	up = flood_fill(map, x, y - 1, height);
	return (right && left && down && up);
}

int	parse_map(char **map, t_game *game)
{
	int		i;
	char	**save_map;

	i = 0;
	while (map[i] && !first_char(map[i], '1'))
		i++;
	game->skipped = i - 2;
	if (!map[i])
	{
		ft_printf(2, "Error, Need map in config file !\n");
		return (0);
	}
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
