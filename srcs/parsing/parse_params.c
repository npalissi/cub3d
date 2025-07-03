/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:17:04 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 02:58:54 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	count_occurrences(char *key, char **m)
{
	char	**key_mapping;
	char	*map;
	char	*pos;
	int		count;
	size_t	key_len;

	count = 0;
	map = concat_map(m);
	if (!map)
		return (0);
	key_mapping = NULL;
	key_len = ft_strlen(key);
	pos = ft_strstr(map, key);
	while (pos != NULL)
	{
		count++;
		ft_strapp(&key_mapping, ft_substr(pos, 0, find_char(pos, '\n')));
		pos = ft_strstr(pos + key_len, key);
	}
	if (ft_arraylen(key_mapping) != 1)
		custom_occu_print(key, key_mapping);
	ft_free_tab(key_mapping);
	free(map);
	return (count);
}

int	parse_occu(char **map)
{
	static char	*key_mapping[6] = {"NO", "SO", "EA", "WE", "F", "C"};
	int			i;
	int			error;

	i = 0;
	error = 1;
	while (i < 6)
	{
		if (count_occurrences(key_mapping[i], map) != 1)
			error = 0;
		i++;
	}
	return (error);
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
	i = 0;
	while (game->map.map[i])
	{
		check_map(game->map.map[i], &error);
		stat[0] += ft_charite(game->map.map[i], 'N');
		stat[1] += ft_charite(game->map.map[i], 'S');
		stat[2] += ft_charite(game->map.map[i], 'E');
		stat[3] += ft_charite(game->map.map[i], 'W');
		i++;
	}
	if ((stat[0] + stat[1] + stat[2] + stat[3]) != 1)
		return (ft_printf(2, "Error, player spawnpoint must be declared only"
				" once and not %d times!\n",
				stat[0] + stat[1] + stat[2] + stat[3]) == 1);
	game->map.h = i;
	game->map.w = len_max(game->map.map);
	return (error);
}
