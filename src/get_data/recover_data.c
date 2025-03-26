/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:18:45 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/25 23:18:22 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int ft_strlenif(char *str, int(*func)(int))
{
	int i;

	i = 0;
	while(*(str + i) && !func(*(str + i)))
		i++;
	return (i);
}

char *find_var_by_key(char *key, char *map)
{
	char *str;
	int	size;
	char *value;

	str = ft_strstr(map, key) + ft_strlen(key);
	while(*str && ft_iswhitespace(*str))
		str++;
	// printf("%s %s\n",key, str);
	size = ft_strlenif(str, &ft_iswhitespace);
	value = ft_substr(str, 0, size);
	if (!value)
		return (0);
	return (value);
}

unsigned int rgba_to_hex(char *color)
{
	unsigned int hex;
	char **rgb;
	int overflow;
	int i;
	int j;


	rgb = ft_split(color, ',');
	if (!rgb)
		return (0);
	j = 0;
	while(j < 3)
	{
		i = ft_atoi(rgb[j], &overflow);
		if (overflow)
			return (0);
		if (i < 0 || i > 255)
			return (0);
		hex = (hex << 8) + i;
		j++;
	}
	ft_free_tab(rgb);
	return (hex);
}

int init_data(t_game *game)
{
	char *floor;
	char *ceiling;

	game->color = (t_color){0, 0};
	game->mat = (t_mat){0, 0, 0, 0};
	floor = find_var_by_key("F", game->str_map);
	ceiling = find_var_by_key("C", game->str_map);
	if (!floor || !ceiling)
		return (0);
	game->color.floor = rgba_to_hex(floor);
	game->color.ceiling = rgba_to_hex(ceiling);
	game->mat.north = find_var_by_key("NO", game->str_map);
	game->mat.south = find_var_by_key("SO", game->str_map);
	game->mat.west = find_var_by_key("WE", game->str_map);
	game->mat.east = find_var_by_key("EA", game->str_map);
	if (!game->color.floor || !game->color.ceiling || !game->mat.north 
		|| !game->mat.south || !game->mat.west || !game->mat.east)
		return (0);
	return (1);
}
