/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:58:51 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 02:28:14 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	fill_map_line(char ***map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		ft_strapp(map, line);
		line = get_next_line(fd);
	}
}

static int	validate_and_open_file(char *file)
{
	int	fd;
	int	len;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(2, "No such file: %s\n", file);
		return (-1);
	}
	len = ft_strlen(file);
	if (len < 4 || file[len - 4] != '.' || file[len - 3] != 'c'
		|| file[len - 2] != 'u' || file[len - 1] != 'b')
	{
		close(fd);
		ft_printf(2, "Bad file format, must be .cub\n");
		return (-1);
	}
	return (fd);
}

int	get_map(char *file, t_game *game)
{
	int		fd;
	t_map	map;

	map.map = NULL;
	fd = validate_and_open_file(file);
	if (fd == -1)
		return (0);
	fill_map_line(&map.map, fd);
	close(fd);
	map.full_map = ft_arraydupe(map.map);
	if (!parse_occu(map.map) || !parse_map(map.map, game))
		return (0);
	game->map = map;
	return (1);
}
