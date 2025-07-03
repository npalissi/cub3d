/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:53:41 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 00:17:42 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	fill_texture(t_texture *tex, int i, char *str)
{
	if (!i)
		tex->north = ft_substr(str, 3, ft_strlen(str) - 2);
	if (i == 1)
		tex->south = ft_substr(str, 3, ft_strlen(str) - 2);
	if (i == 2)
		tex->west = ft_substr(str, 3, ft_strlen(str) - 2);
	if (i == 3)
		tex->east = ft_substr(str, 3, ft_strlen(str) - 2);
}

void	close_fds_basic(int fd[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (fd[i] > 2)
			close(fd[i]);
		i++;
	}
}

static void	init_co(char *(*co)[4], int lit)
{
	if (lit)
	{
		(*co)[0] = "north";
		(*co)[1] = "south";
		(*co)[2] = "east";
		(*co)[3] = "west";
	}
	(*co)[0] = "NO ";
	(*co)[1] = "SO ";
	(*co)[2] = "WE ";
	(*co)[3] = "EA ";
}

int	check_texture(t_game *game)
{
	int		fd[4];
	int		i;
	char	*co[4];
	int		error;

	init_co(&co, 1);
	printf("%s", co[0]);
	fd[0] = open(game->texture.north, O_RDONLY);
	fd[1] = open(game->texture.south, O_RDONLY);
	fd[2] = open(game->texture.east, O_RDONLY);
	fd[3] = open(game->texture.west, O_RDONLY);
	i = 0;
	error = 1;
	while (i < 4)
	{
		if (fd[i] == -1)
		{
			ft_printf(2, "Error while opening file for %s texture !\n", co[i]);
			error = 0;
		}
		i++;
	}
	close_fds_basic(fd);
	return (error);
}

int	get_textures(t_game *game)
{
	char	**save_map;
	char	*co[4];
	int		i;

	i = 0;
	init_co(&co, 0);
	save_map = game->map.map;
	while (i < 4)
	{
		game->map.map = save_map;
		while (!ft_strcmp(ft_substr(*game->map.map, 0, 3),
				co[i]) && *game->map.map)
			game->map.map++;
		if (*game->map.map)
			fill_texture(&game->texture, i++, ft_substr(*game->map.map, 2,
					ft_strlen(*game->map.map) - 3));
		else
		{
			ft_printf(2, "Error, Not all textures path are there\
					 ! Missing at least: %s\n", co[i]);
			return (0);
		}
	}
	game->map.map = save_map;
	return (check_texture(game));
}
