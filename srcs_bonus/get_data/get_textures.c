/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:53:41 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 13:34:10 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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
	if (i == 4)
		tex->door = ft_substr(str, 3, ft_strlen(str) - 2);
}

void	close_fds(int fd[5])
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (fd[i] > 2)
			close(fd[i]);
		i++;
	}
}

void	check_all_textures(const char *paths[5],
	char *co[5], int *error)
{
	int	i[2];
	int	fd[5];

	i[0] = -1;
	while (++i[0] < 5)
	{
		i[1] = open(paths[i[0]], O_DIRECTORY);
		if (i[1] != -1)
		{
			close(i[1]);
			ft_printf(2, "Error: %s is a directory, not a file\n", co[i[0]]);
			*error = 0;
			fd[i[0]] = -1;
		}
		else
		{
			fd[i[0]] = open(paths[i[0]], O_RDONLY);
			if (fd[i[0]] == -1)
			{
				ft_printf(2, "Error while opening %s texture file\n", co[i[0]]);
				*error = 0;
			}
		}
	}
	close_fds(fd);
}

int	check_texture(t_game *game)
{
	const char		*paths[5] = {
		game->texture.north,
		game->texture.south,
		game->texture.east,
		game->texture.west,
		game->texture.door
	};
	static char		*co[5] = {"north", "south", "east", "west", "door"};
	int				error;

	error = 1;
	check_all_textures(paths, co, &error);
	return (error);
}

int	get_textures(t_game *game)
{
	char		**save_map;
	static char	*co[5] = {"NO ", "SO ", "WE ", "EA ", "DO "};
	int			i;

	i = 0;
	save_map = game->map.map;
	while (i < 5)
	{
		game->map.map = save_map;
		while (!ft_strcmp(ft_substr(*game->map.map, 0, 3), co[i])
			&& *game->map.map)
			game->map.map++;
		if (*game->map.map)
			fill_texture(&game->texture, i++, ft_substr(*game->map.map, 2,
					ft_strlen(*game->map.map) - 3));
		else
		{
			ft_printf(2, "Error, Not all textures path are there ! "
				"Missing at least: %s\n", co[i]);
			return (0);
		}
	}
	game->map.map = save_map;
	return (check_texture(game));
}
