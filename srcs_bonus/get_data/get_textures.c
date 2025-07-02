/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:53:41 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/02 22:06:57 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void    fill_texture(t_texture *tex, int i, char *str)
{
    // char *temp;
    // char *clean_path;
    
    // // Extraire le chemin et nettoyer les espaces/retours à la ligne
    // temp = ft_substr(str, 3, ft_strlen(str) - 3);
    // clean_path = ft_strtrim(temp, " \t\n\r");
    // dh_free(temp); // Libérer la mémoire temporaire
    
    // if (!i)
    //     tex->north = clean_path;
    // else if (i == 1)
    //     tex->south = clean_path;
    // else if (i == 2)
    //     tex->west = clean_path;
    // else if (i == 3)
    //     tex->east = clean_path;
    // else if (i == 4)
    //     tex->door = clean_path;
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

void    close_fds_basic(int fd[4])
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

void    close_fds(int fd[5])
{
    int i;

    i = 0;
    while (i < 5)
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
    close_fds_basic(fd);
    return (error);
}

int check_texture_optional(t_game *game)
{
    int fd[5];
    int i;
    char *co[5] = {"north ", "south ", "east ", "west ", "door "};
    int error;

    fd[0] = open(game->texture.north, O_RDONLY);
    fd[1] = open(game->texture.south, O_RDONLY);
    fd[2] = open(game->texture.east, O_RDONLY);
    fd[3] = open(game->texture.west, O_RDONLY);
    fd[4] = open(game->texture.door, O_RDONLY);
    i = 0;
    error = 1;
    while (i < 5)
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

int has_doors_in_map(t_game *game)
{
    int i = 0;
    int j;
    
    while (game->map.map[i])
    {
        j = 0;
        while (game->map.map[i][j])
        {
            if (game->map.map[i][j] == 'D')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int get_textures(t_game *game)
{
    char **save_map;
    char *co[5] = {"NO ", "SO ", "WE ", "EA ", "DO "};
    int i;
    
    i = 0;
    save_map = game->map.map;
    while (i < 5)
    {
        game->map.map = save_map;
        while (!ft_strcmp(ft_substr(*game->map.map, 0, 3), co[i]) && *game->map.map)
            game->map.map++;
        if (*game->map.map)
            fill_texture(&game->texture, i++, ft_substr(*game->map.map, 2, ft_strlen(*game->map.map) - 3));
        else
        {
            if (i == 4)
            {
                printf("No door texture find, starting with random texture for door !\n");
                break ;
            }
            ft_printf(2, "Error, Not all textures path are there ! Missing at least: %s\n", co[i]);
            return (0);
        }
    }
        game->map.map = save_map;
    return (check_texture(game));
}
