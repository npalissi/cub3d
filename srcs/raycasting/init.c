/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/26 17:29:13 by edubois-         ###   ########.fr       */
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
void	fill_crowbar(t_game *game, char crowbar[50])
{
	int y;
	int x;

	y = 919;
	x = 271;
	game->bar.bar = mlx_new_image_from_file(game->mlx, crowbar, &y, &x);
	if (!game->bar.bar)
	{
		ft_printf(2, "Error: failed to load crowbar image\n");
		return ;
	}
	y = 0;
	while (y < 271)
	{
		x = 0;
		while (x < 919)
		{
			mlx_color	*pixel = &game->bar.c[y * 919 + x];
			
			*pixel = mlx_get_image_pixel(game->mlx, game->bar.bar, x, y);
			x++;
		}
		y++;
	}
}

void	init_crow(t_game *game)
{
	static char crowbar[50] = "textures/crowbar.png";
	int fd;
	
	fd = open(crowbar, O_RDONLY);
	game->bar.valid = 1;
	if (fd == -1)
	{
		ft_printf(2, "Textures for crowbar have been modified, starting without crowbar !\n");
		game->bar.valid = 0;
	}
	else
	{
		game->bar.c = malloc(sizeof(mlx_color) * 919 * 271);
		if (!game->bar.c)
			return ;
		fill_crowbar(game, crowbar);
	}		
	if (fd > 2)
		close(fd);
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
