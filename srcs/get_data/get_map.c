/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:58:51 by edubois-          #+#    #+#             */
/*   Updated: 2025/06/18 12:34:45 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    fill_map_line(char ***map, int fd)
{
	char *line;
	
	line = get_next_line(fd);
	while(line)
	{
		ft_strapp(map, line);
		line = get_next_line(fd);
	}
}

int get_map(char *file, t_game *game)
{
    int fd;
    t_map map;

    map.map = NULL;
    fd = open (file, O_RDONLY);
    if (fd == -1)
    {
        ft_printf(2, "No such file: %s\n", file);
        return (0);
    }
    if (!ft_strcmp(ft_substr(file, ft_strlen(file) - 4, 4), ".cub"))
    {
        if (fd > 2)
            close(fd);
        ft_printf(2, "Bad file format, must be .cub\n");
        return (0);
    }
    fill_map_line(&map.map, fd);
    close(fd);
    if (!parse_occu(map.map) || !parse_map(map.map))
        return (0);
    game->map = map;
    return (1);
}
