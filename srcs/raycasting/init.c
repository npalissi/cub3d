/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/24 17:39:47 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

void	init_frame_buffer(t_game *game)
{
	game->frame_buffer = malloc(sizeof(mlx_color) * WIDTH * HEIGHT);
	if (!game->frame_buffer)
	{
		ft_printf(2, "Error: Failed to allocate frame buffer\n");
		cleanup_game(game);
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		ft_printf(2, "Error: Failed to create image\n");
		cleanup_game(game);
		exit(1);
	}
}

int init_all(t_game *game)
{
	game->mini.b = malloc(sizeof(mlx_color) * 25 * 25);
	if (!game->mini.b)
	{
		ft_printf(2, "Error failled allocation for background pixel\n");
		return (0);
	}
	game->mini.w = malloc(sizeof(mlx_color) * 25 * 25);
	if (!game->mini.w)
	{	
		free(game->mini.b);
		ft_printf(2, "Error failled allocation for wall pixel\n");
		return (0);
	}
	game->mini.c = malloc(sizeof(mlx_color) * 25 * 25);
	if (!game->mini.c)
	{
		free(game->mini.b);
		free(game->mini.w);
		ft_printf(2, "Error failled allocation for character pixel\n");
		return (0);
	}
	return (1);
}

void	init_pixel(t_game *game)
{
	int y;
	int x;
	
	if (!init_all(game))
		return ;
	y = 0;
	while (y != 25)
	{
		x = 0;
		while (x != 25)
		{
			game->mini.c[y * 25 + x] = mlx_get_image_pixel(game->mlx, game->mini.character, x, y);
			game->mini.b[y * 25 + x] = mlx_get_image_pixel(game->mlx, game->mini.back, x, y);
			game->mini.w[y * 25 + x] = mlx_get_image_pixel(game->mlx, game->mini.wall, x, y);
			x++;
		}
		y++;
	}
}

void	init_minimap(t_game *game)
{
	static char	wall[50] = "minimap_textures/wall.png";
	static char	background[50] = "minimap_textures/background.png";
	static char	character[50] = "minimap_textures/character.png";
	int			fd[3];
	static int	w = 25;

	game->mini.valid = 1;
	fd[0] = open(wall, O_RDONLY);
	fd[1] = open(background, O_RDONLY);
	fd[2] = open(character, O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1)
	{
		ft_printf(2, "Textures for minimap have been modified, starting without minimap !\n");
		game->mini.valid = 0;
	}
	else
	{
		ft_array_replace(game->mini.map, "NSWE", '0');
		game->mini.wall = mlx_new_image_from_file(game->mlx, wall, &w, &w);
		game->mini.back = mlx_new_image_from_file(game->mlx, background, &w, &w);
		game->mini.character = mlx_new_image_from_file(game->mlx, character, &w, &w);
		if (!game->mini.wall || !game->mini.back || !game->mini.character)
		{
			ft_printf(2, "Error, could not load minimap texture, starting without minimap\n");
			game->mini.valid = 0;
		}
	}
	init_pixel(game);
}
