/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:54:47 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 02:43:28 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	len_max(char **str)
{
	int	max;
	int	temp;

	max = ft_strlen(*str);
	while (*str)
	{
		temp = ft_strlen(*str);
		if (temp > max)
			max = temp;
		str++;
	}
	return (max);
}

int	find_y(char **map, int i)
{
	int	y;

	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			if (map[i][y] == 'N' || map[i][y] == 'S'
				|| map[i][y] == 'W' || map[i][y] == 'E')
				return (y);
			y++;
		}
		i++;
	}
	return (-1);
}

int	find_x(char **map, int i)
{
	int	y;

	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			if (map[i][y] == 'N' || map[i][y] == 'S'
				|| map[i][y] == 'W' || map[i][y] == 'E')
				return (i);
			y++;
		}
		i++;
	}
	return (-1);
}

char	*concat_map(char **map)
{
	size_t	total_len;
	size_t	len;
	int		i;
	char	*result;
	char	*ptr;

	i = 0;
	total_len = 0;
	while (map && map[i])
		total_len += ft_strlen(map[i++]);
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	ptr = result;
	i = 0;
	while (map && map[i])
	{
		len = ft_strlen(map[i]);
		ft_memcpy(ptr, map[i], len);
		ptr += len;
		i++;
	}
	*ptr = '\0';
	return (result);
}

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i])
		return (i);
	return (-1);
}
