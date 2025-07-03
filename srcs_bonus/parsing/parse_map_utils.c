/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:43:47 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 02:34:10 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	is_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	return (str[i] == '\0');
}

int	match_key(t_game *game, char *str)
{
	if (ft_strstr(str, game->color.cl)
		|| ft_strstr(str, game->color.fl)
		|| ft_strstr(str, game->texture.north)
		|| ft_strstr(str, game->texture.south)
		|| ft_strstr(str, game->texture.door)
		|| ft_strstr(str, game->texture.east)
		|| ft_strstr(str, game->texture.west))
		return (1);
	return (0);
}

int	check_full_map(t_game *game)
{
	char	*str;
	int		empty[2];

	empty[1] = 0;
	while (*game->map.full_map)
	{
		empty[0] = 1;
		str = *game->map.full_map++;
		empty[0] = is_empty_line(str);
		if (!empty[0])
		{
			--game->mini.skipped;
			if (!game->mini.skipped)
				break ;
			if (match_key(game, str))
				continue ;
			else
				empty[1] += ft_printf(2, "Error, files must be clean,"
						RED"%s\n"RESET, str);
		}
	}
	return (empty[1]);
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
