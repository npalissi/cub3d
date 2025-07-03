/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 03:44:56 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

static mlx_image	*get_wall_texture(t_game *game, t_ray ray)
{
	if (ray.wall_side == 0)
		return (&game->texture.north_img);
	else if (ray.wall_side == 1)
		return (&game->texture.south_img);
	else if (ray.wall_side == 2)
		return (&game->texture.west_img);
	else
		return (&game->texture.east_img);
}

void	draw_vertical_line_no_stretch(t_game *game, int x, float wall_height,
	t_ray ray)
{
	t_render_vars	vars;

	vars.game = game;
	vars.ray = ray;
	init_render_vars(&vars, x, wall_height);
	render_ceiling_and_floor(&vars);
	vars.texture = get_wall_texture(game, ray);
	if (!vars.texture || !*vars.texture)
		return ;
	setup_texture_mapping(&vars, wall_height);
	render_wall_column(&vars);
}
