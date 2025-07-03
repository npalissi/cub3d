/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 02:37:51 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 03:40:53 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	put_region_to_array(mlx_color *fb, t_vec2 start,
	t_vec2 size, mlx_color *src)
{
	uint32_t	y;
	uint32_t	sindex;
	uint32_t	index;
	uint32_t	x;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			sindex = y * size.x + x;
			index = (start.y + y) * WIDTH + (start.x + x);
			if (src[sindex].a != 0)
				fb[index] = src[sindex];
			x++;
		}
		y++;
	}
}

void	init_render_vars(t_render_vars *vars, int x, float wall_height)
{
	vars->start_y = (HEIGHT - (int)wall_height) / 2;
	vars->end_y = vars->start_y + (int)wall_height;
	if (vars->start_y < 0)
		vars->start_y = 0;
	if (vars->end_y > HEIGHT)
		vars->end_y = HEIGHT;
	vars->column = vars->game->frame_buffer + x;
}

void	render_ceiling_and_floor(t_render_vars *vars)
{
	int	y;

	y = 0;
	while (y < vars->start_y)
	{
		vars->column[y * WIDTH] = vars->game->color.ceiling;
		y++;
	}
	y = vars->end_y;
	while (y < HEIGHT)
	{
		vars->column[y * WIDTH] = vars->game->color.floor;
		y++;
	}
}

void	setup_texture_mapping(t_render_vars *vars, float wall_height)
{
	vars->step = (float)vars->game->texture.height / wall_height;
	vars->tex_x = (int)(vars->ray.wall_x * vars->game->texture.width);
	if (vars->tex_x < 0)
		vars->tex_x = 0;
	if (vars->tex_x >= vars->game->texture.width)
		vars->tex_x = vars->game->texture.width - 1;
	if (wall_height > HEIGHT)
		vars->tex_pos = ((wall_height - HEIGHT) / 2.0f) * vars->step;
	else
		vars->tex_pos = 0.0f;
}

void	render_wall_column(t_render_vars *vars)
{
	int				y;
	int				tex_y;
	mlx_color		color;

	y = vars->start_y;
	while (y < vars->end_y)
	{
		tex_y = (int)vars->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= vars->game->texture.height)
			tex_y = vars->game->texture.height - 1;
		color = mlx_get_image_pixel(vars->game->mlx, *vars->texture,
				vars->tex_x, tex_y);
		vars->column[y * WIDTH] = color;
		vars->tex_pos += vars->step;
		y++;
	}
}
