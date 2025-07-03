/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:42:31 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 13:11:17 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

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

int	init_mlx(t_game *game)
{
	static mlx_window_create_info	info = {0};

	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf(2, "Error: Failed to initialize MLX\n");
		return (0);
	}
	info.title = "cub3d_bonus";
	info.width = WIDTH;
	info.height = HEIGHT;
	info.is_resizable = false;
	game->win = mlx_new_window(game->mlx, &info);
	if (!game->win)
	{
		ft_printf(2, "Error: Failed to create window\n");
		mlx_destroy_context(game->mlx);
		return (0);
	}
	return (1);
}
