/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:05 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/02 19:27:30 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

static int	init_mlx(t_game *game)
{
	mlx_window_create_info info = {0};

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

static void	setup_hooks(t_game *game)
{
	mlx_on_event(game->mlx, game->win, MLX_WINDOW_EVENT, close_win, game);
	mlx_on_event(game->mlx, game->win, MLX_KEYDOWN, key_press, game);
	mlx_on_event(game->mlx, game->win, MLX_KEYUP, key_release, game);
	mlx_on_event(game->mlx, game->win, MLX_MOUSEDOWN, mouse_down, game);
	mlx_on_event(game->mlx, game->win, MLX_MOUSEUP, mouse_up, game);
	mlx_on_event(game->mlx, game->win, MLX_MOUSEWHEEL, mouse_wheel, game);
	mlx_add_loop_hook(game->mlx, draw_loop, game);
	mlx_set_fps_goal(game->mlx, 1000);
}

void	cleanup_game(t_game *game)
{

	if (game->mini.c)
		dh_free(game->mini.c);
	if (game->d)
		dh_free(game->d);
	if (game->color.cl)
		dh_free(game->color.cl);
	if (game->color.cl)
		dh_free(game->color.cl);
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
	if (game->frame_buffer)
		free(game->frame_buffer);
	if (game->bar.item[1])
		mlx_destroy_image(game->mlx, game->bar.item[1]);
	if (game->bar.item[0])
		mlx_destroy_image(game->mlx, game->bar.item[0]);
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

int check_full_map(t_game *game)
{
	char *str;
	int empty[2];
	int i;
	
	empty[1] = 0;
	while (*game->map.full_map)
	{
		empty[0] = 1;
		str = *game->map.full_map++;
		i = 0;
		while (str[i] && ft_iswhitespace(str[i]))
			i++;
		if (str[i])			
			empty[0] = 0;
		if (!empty[0])
		{
			// Vérifier si c'est une ligne de texture ou couleur valide
			if (ft_strstr(str, "WE ") || ft_strstr(str, "EA ") || ft_strstr(str, "NO ") || ft_strstr(str, "SO ") || ft_strstr(str, "DO ") || 
				ft_strstr(str, "F ") || ft_strstr(str, "C "))
				continue;
			if ((ft_strlen(str) == ft_strlen(game->map.map[0]) - 1) && first_char(str, '1'))
				break ;
			else
				empty[1] += ft_printf(2, "Error, files must be clean, " RED"%s\n"RESET, str);
			}
		}
	return (empty[1]);
}

int main(int argc, char **argv)
{
	t_game game = {0};

	if (argc != 2)
	{
		ft_printf(2, "Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (!get_map(argv[1], &game) || !get_textures(&game) || 
		!get_colors(&game) || !cut_map(&game))
		return (1);
	
	if (!init_mlx(&game))
		return (1);
	if (!load_textures(&game) )
	{
		cleanup_game(&game);
		return (1);
	}
	
	// Afficher le message de chargement
	mlx_clear_window(game.mlx, game.win, (mlx_color){{255, 0, 0, 0}});
	mlx_color white = {{255, 255, 255, 255}};
	mlx_string_put(game.mlx, game.win, WIDTH/2 - 80, HEIGHT/2, white, "Loading textures...");
	
	init_item(&game, "textures/wraith_exit.png", 1);
	init_item(&game, "textures/wraith_walking.png", 2);
	init_item(&game, "textures/wraith_transition.png", 3);
	init_item(&game, "textures/crowbar.png", 0);
	init_minimap(&game);
	load_map_data(&game);
	init_frame_buffer(&game);
	init_game(&game);
	setup_hooks(&game);
	
	mlx_loop(game.mlx);
	
	cleanup_game(&game);
	return (0);
}
