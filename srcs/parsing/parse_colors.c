/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:53:49 by edubois-          #+#    #+#             */
/*   Updated: 2025/05/12 14:49:00 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int make_rgb(int *overflow, char **rgb, int i, int j)
{
	int hex;

	hex = 0;
	if (ft_arraylen(rgb) != 3)
	*overflow = 2;
	while(++j < 3 && rgb[j] && !*overflow)
	{
		i = ft_atoi(rgb[j], overflow);
		if (*overflow)
		return (0);
		if (i < 0 || i > 255)
		{
			*overflow = 1;
			return (0);
		}
		hex = (hex << 8) + i;
	}
	ft_free_tab(rgb);
	return (hex);	
}

unsigned int rgba_to_hex(char *color, int *overflow)
{
	char **rgb;
	int i;
	int j;
	
	i = 0;
	j = -1;
	rgb = ft_split(color, ',');
	if (!rgb)
		return (0);
	return (make_rgb(overflow, rgb, i, j));
}

