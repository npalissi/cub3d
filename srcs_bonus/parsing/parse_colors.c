/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:53:49 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/02 22:06:57 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

mlx_color make_rgb(int *overflow, char **rgb)
{
	int hex;
	mlx_color color;
	
	hex = 0;
	if (ft_arraylen(rgb) != 3)
		*overflow = 2;
	hex = ft_atoi(rgb[0], overflow);
	if (*overflow || hex < 0 || hex > 255)
		*overflow = 1;
	color.r = hex;
	hex = ft_atoi(rgb[1], overflow);
	if (*overflow || hex < 0 || hex > 255)
		*overflow = 1;
	color.g = hex;
	hex = ft_atoi(rgb[2], overflow);
	if (*overflow || hex < 0 || hex > 255)
		*overflow = 1;
	color.b = hex;
	color.a = 255;
	ft_free_tab(rgb);
	return (color);	
}

mlx_color rgba_to_hex(char *color, int *overflow)
{
	char **rgb;
	mlx_color result = {0};
	
	rgb = ft_split(color, ',');
	if (!rgb || ft_arraylen(rgb) != 3)
	{
		*overflow = 1;
		return (result);
	}
	return (make_rgb(overflow, rgb));
}

