/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/23 19:56:29 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

mlx_color	calculate_wall_color(mlx_color base_color)
{
	return (base_color);
}

mlx_color	get_ceiling_color(void)
{
	mlx_color	color;
	
	color.a = 255;
	color.b = 45;
	color.g = 40;
	color.r = 40;
	return (color);
}

mlx_color	get_floor_color(void)
{
	mlx_color	color;

	color.a = 255;
	color.b = 40;
	color.g = 50;
	color.r = 60;
	return (color);
}
