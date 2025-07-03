/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/02 23:24:08 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

int	init_mlx(t_game *game)
{
	mlx_window_create_info	info;

	info = (mlx_window_create_info){0};
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf(2, "Error: Failed to initialize MLX\n");
		return (0);
	}
	info.title = "Cub3D";
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

void	setup_hooks(t_game *game)
{
	mlx_on_event(game->mlx, game->win, MLX_WINDOW_EVENT, close_win, game);
	mlx_on_event(game->mlx, game->win, MLX_KEYDOWN, key_press, game);
	mlx_on_event(game->mlx, game->win, MLX_KEYUP, key_release, game);
	mlx_add_loop_hook(game->mlx, draw_loop, game);
	mlx_set_fps_goal(game->mlx, 60);
}
