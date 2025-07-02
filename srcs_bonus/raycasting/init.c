/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/02 22:06:18 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	init_frame_buffer(t_game *game)
{
	game->frame_buffer = malloc(sizeof(mlx_color) * WIDTH * HEIGHT);
	if (!game->frame_buffer)
	{
		ft_printf(2, "Error: Failed to allocate frame buffer\n");
		cleanup_game(game);
		exit(1);
	}
}

void	init_pixel(t_game *game)
{
	int y;
	int x;
	
	game->mini.c = malloc(sizeof(mlx_color) * 25 * 25);
	if (!game->mini.c)
	{
		ft_printf(2, "Error failled allocation for character pixel\n");
		return ;
	}
	y = 0;
	while (y != 25)
	{
		x = 0;
		while (x != 25)
		{
			game->mini.c[y * 25 + x] = mlx_get_image_pixel(game->mlx, game->mini.character, x, y);
			x++;
		}
		y++;
	}
}
void	fill_item(t_game *game, char path[50], int type)
{
	int y;
	int x;

	game->bar.item[type] = mlx_new_image_from_file(game->mlx, path, &y, &x);
	if (!game->bar.item[type])
	{
		if (!type)
			ft_printf(2, "Error: failed to load crowbar image\n");
			else
			ft_printf(2, "Error: failed to load kunai image %d\n", type);
		game->bar.valid[type] = 0;
		return ;
	}
	while (x < game->bar.x[type])
	{
		y = 0;
		while (y < game->bar.x[type])
		{
			mlx_color	*pixel = &game->bar.c[game->bar.type][x * game->bar.y[type] + y];
			if (!type)
				*pixel = mlx_get_image_pixel(game->mlx, game->bar.item[type], y, x);
			y++;
		}
		x++;
	}
	game->bar.time[type] = current_time();
}

void	init_item(t_game *game, char path[50], int type)
{
	int fd;
	uint64_t	size;

	fd = open(path, O_RDONLY);
	game->bar.valid[type] = 1;
	if (fd == -1)
	{
		if (!type)
			ft_printf(2, "Textures for crowbar have been modified, starting without crowbar !\n");
		else
			ft_printf(2, "Textures for kunai have been modified, starting without kunai %d!\n", type);
		game->bar.valid[type] = 0;
		return ;
	}
	else
	{
		game->bar.x[0] = 651;
		game->bar.x[1] = 134400;
		game->bar.x[2] = 46080;
		game->bar.x[3] = 46080;
		game->bar.y[0] = 271;
		game->bar.y[1] = 1080;
		game->bar.y[2] = 1080;
		game->bar.y[3] = 1080;
		if ((!type && (HEIGHT < 271 || WIDTH < 140)) || (type && (HEIGHT < 1080 || WIDTH < 1920)))
		{
			ft_printf(2, "Error, windows is to tight to put item, starting without ");
			if (!type)
				ft_printf(2, "crowbar\n");
			else
				ft_printf(2, "kunai %d\n", type);
			game->bar.valid[type] = 0;
			return ;
		}
		size = game->bar.x[type] * game->bar.y[type] * (sizeof(mlx_color));
		game->bar.size[type] = size;
		game->bar.c[type] = (mlx_color *) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
		if (game->bar.c[type] == MAP_FAILED)
			return ;
		fill_item(game, path, type);
	}		
	if (fd > 2)
		close(fd);
	game->bar.wait[type] = 30;
		if (!type)
		game->bar.wait[type] = 200;
	game->bar.type = type;
}


void	init_minimap(t_game *game)
{
	static char	wall[50] = "minimap_textures/half_wall.png";
	static char	background[50] = "minimap_textures/half_background.png";
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
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);
		ft_array_replace(game->mini.map, "NSWE", '0');
		game->mini.wall = mlx_new_image_from_file(game->mlx, wall, &w, &w);
		game->mini.back = mlx_new_image_from_file(game->mlx, background, &w, &w);
		game->mini.character = mlx_new_image_from_file(game->mlx, character, &w, &w);
		if (!game->mini.wall || !game->mini.back || !game->mini.character)
		{
			ft_printf(2, "Error, could not load minimap texture, starting without minimap\n");
			game->mini.valid = 0;
		}
		init_pixel(game);
	}
}
