/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:18:45 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/25 19:52:34 by npalissi         ###   ########.fr       */
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
	size = ft_strlenif(str, &ft_iswhitespace);
	value = ft_substr(str, 0, size);
	if (!value)
		return (0);
	return (value);
}

int init_data(t_game *game)
{
	game->color.floor = find_var_by_key("F", game->str_map);
	game->color.ceiling = find_var_by_key("C", game->str_map);
	game->mat.north = find_var_by_key("NO", game->str_map);
	// game->mat.south = find_var_by_key("SO", game->str_map);
	// game->mat.west = find_var_by_key("WE", game->str_map);
	// game->mat.east = find_var_by_key("EA", game->str_map);
	printf("color Floor   :%s\n", game->color.floor);
	printf("color Ceiling :%s\n", game->color.ceiling);
	printf("mat   north   :%s\n", game->mat.north);
	// printf("mat   south   :%s\n", game->mat.south);
	// printf("mat   west    :%s\n", game->mat.west);
	// printf("mat   east    :%s\n", game->mat.east);
	return (1);
}