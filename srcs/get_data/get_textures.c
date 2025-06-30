/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:53:41 by edubois-          #+#    #+#             */
/*   Updated: 2025/06/28 16:06:57 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    fill_texture(t_texture *tex, int i, char *str)
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

void    close_fds(int fd[4])
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (fd[i] > 2)
            close(fd[i]);
        i++;
    }
}

int check_texture(t_game *game)
{
    int fd[4];
    int i;
    char *co[4] = {"north ", "south ", "east ", "west "};
    int error;

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
    close_fds(fd);
    return (error);
}

int get_textures(t_game *game)
{
    char **save_map;
    char *co[4] = {"NO ", "SO ", "WE ", "EA "};
    int i;
    
    i = 0;
    save_map = game->map.map;
    while (i < 4)
    {
        game->map.map = save_map;
        while (!ft_strcmp(ft_substr(*game->map.map, 0, 3), co[i]) && *game->map.map)
            game->map.map++;
        if (*game->map.map)
            fill_texture(&game->texture, i++, ft_substr(*game->map.map, 2, ft_strlen(*game->map.map) - 3));
        else
        {
            ft_printf(2, "Error, Not all textures path are there ! Missing at least: %s\n", co[i]);
            return (0);
        }
    }
        game->map.map = save_map;
    return (check_texture(game));
}
