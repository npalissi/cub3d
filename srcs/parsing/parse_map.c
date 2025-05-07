/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:15:04 by edubois-          #+#    #+#             */
/*   Updated: 2025/05/07 13:53:30 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void fill_map(char **map, int i)
{
	int j;
	int lm;

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

int is_in_bounds(char **map, int x, int y, int height)
{
	int row_len;

    if (y < 0 || y >= height)
        return 0;
    if (!map[y])
        return 0;
    row_len = ft_strlen(map[y]);
    if (x < 0 || x >= row_len)
        return 0;
    return 1;
}

int flood_fill(char **map, int x, int y, int height, int width)
{
    int right;
	int left ;
	int down ;
	int up;
	
	if (!is_in_bounds(map, x, y, height))
        return 0;
    if (map[y][x] != EMPTY && map[y][x] != 'N' && map[y][x] != 'S'
        && map[y][x] != 'E' && map[y][x] != 'W')
        return 1;
    map[y][x] = VISITED;
	right = flood_fill(map, x + 1, y, height, width);
	left = flood_fill(map, x - 1, y, height, width);
	down = flood_fill(map, x, y + 1, height, width);
    up = flood_fill(map, x, y - 1, height, width);
    return (right && left && down && up);
}

int parse_map(char **map)
{
	int i = 0;
	
	while (map[i] && !first_char(map[i], '1'))
		i++;
	if (!map[i])
	{
		ft_printf(2, "Error, Need map in config file !\n");
		return (0);
	}
	fill_map(map, i);
	if (!flood_fill(map, find_y(map, i), find_x(map, i),
		ft_arraylen(map), len_max(map) - 1))
	{
		ft_printf(2, "Error, The map needs to be closed !\n");
		return (0);
	}
	return (1);
}
