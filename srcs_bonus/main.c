/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:05 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 04:15:17 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

static void	setup_hooks(t_game *game)
{
	mlx_on_event(game->mlx, game->win, MLX_WINDOW_EVENT, close_win, game);
	mlx_on_event(game->mlx, game->win, MLX_KEYDOWN, key_press, game);
	mlx_on_event(game->mlx, game->win, MLX_KEYUP, key_release, game);
	mlx_on_event(game->mlx, game->win, MLX_MOUSEDOWN, mouse_down, game);
	mlx_on_event(game->mlx, game->win, MLX_MOUSEUP, mouse_up, game);
	mlx_on_event(game->mlx, game->win, MLX_MOUSEWHEEL, mouse_wheel, game);
	mlx_add_loop_hook(game->mlx, draw_loop, game);
	mlx_set_fps_goal(game->mlx, 60);
}

void	clean_all(t_game *game )
{
	if (game->bar.item[2])
		mlx_destroy_image(game->mlx, game->bar.item[2]);
	if (game->bar.item[3])
		mlx_destroy_image(game->mlx, game->bar.item[3]);
	if (game->texture.north_img)
		mlx_destroy_image(game->mlx, game->texture.north_img);
	if (game->texture.south_img)
		mlx_destroy_image(game->mlx, game->texture.south_img);
	if (game->texture.west_img)
		mlx_destroy_image(game->mlx, game->texture.west_img);
	if (game->texture.east_img)
		mlx_destroy_image(game->mlx, game->texture.east_img);
	if (game->texture.door_img)
		mlx_destroy_image(game->mlx, game->texture.door_img);
	if (game->mini.back)
		mlx_destroy_image(game->mlx, game->mini.back);
	if (game->mini.wall)
		mlx_destroy_image(game->mlx, game->mini.wall);
	if (game->mini.character)
		mlx_destroy_image(game->mlx, game->mini.character);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_context(game->mlx);
}

void	cleanup_game(t_game *game)
{
	if (game->mini.c)
		dh_free(game->mini.c);
	if (game->d)
		dh_free(game->d);
	dh_free(game->color.cl);
	if (game->color.cl)
		dh_free(game->color.cl);
	if (game->mini.c)
		free(game->mini.c);
	ft_free_tab(game->mini.map);
	ft_free_tab(game->map.full_map);
	if (game->bar.item[0] != (void *)-1)
		munmap(game->bar.item[0], game->bar.size[0]);
	if (game->bar.item[1] != (void *)-1)
		munmap(game->bar.item[1], game->bar.size[1]);
	if (game->bar.item[2] != (void *)-1)
		munmap(game->bar.item[2], game->bar.size[2]);
	if (game->bar.item[3] != (void *)-1)
		munmap(game->bar.item[2], game->bar.size[3]);
	dh_free(game->frame_buffer);
	if (game->bar.item[1])
		mlx_destroy_image(game->mlx, game->bar.item[1]);
	if (game->bar.item[0])
		mlx_destroy_image(game->mlx, game->bar.item[0]);
	clean_all(game);
}

void	start_game(t_game *game)
{
	printf("Loading textures, it may be long...\n");
	init_item(game, "textures_sprites/wraith_exit.png", 1);
	init_item(game, "textures_sprites/wraith_walking.png", 2);
	init_item(game, "textures_sprites/wraith_transition.png", 3);
	init_item(game, "textures_sprites/crowbar.png", 0);
	init_minimap(game);
	load_map_data(game);
	init_frame_buffer(game);
	init_game(game);
	setup_hooks(game);
	mlx_loop(game->mlx);
	cleanup_game(game);
}

int	main(int argc, char **argv)
{
	static t_game	game = {0};

	if (argc != 2)
	{
		ft_printf(2, "Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (!get_map(argv[1], &game) || !get_textures(&game)
		|| !get_colors(&game) || !cut_map(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	if (!init_mlx(&game) || !load_textures(&game) || check_full_map(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	start_game(&game);
}
