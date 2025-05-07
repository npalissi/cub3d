/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:53:41 by edubois-          #+#    #+#             */
/*   Updated: 2025/05/07 15:09:47 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int fill_paths(char ***paths, char **full_map)
{
    char **save_map;
    char *co[4] = {"NO ", "SO ", "WE ", "EA "};
    int i;
    
    i = 0;
    save_map = full_map;
    while (i < 4)
    {
        full_map = save_map;
        while (!ft_strcmp(ft_substr(*full_map, 0, 3), co[i]) && *full_map)
        full_map++;
        if (*full_map)
        {
            ft_strapp(paths, ft_substr(*full_map, 3, ft_strlen(*full_map) - 4));
            i++;
        }
        else
        {
            ft_printf(2, "Error, Not all textures path are there !\n");
            return (0);
        }
    }
    return (1);
}

int get_textures(char ***map, int *fd)
{
    char **paths;
    int i;
    
    paths = NULL;
    i = 0;
    fd = ft_calloc(sizeof(int) , 5);
    if (!fd)
        return (0);
    if (!fill_paths(&paths, *map))
        return (0);
    while (i < 4)
    {
        fd[i] = open(paths[i], O_RDONLY);
        if (fd[i] == -1)
        {
            while (i)
            {
                if (fd[i] > 2)
                    close(fd[i--]);
            }
            ft_printf(2, "Error while opening textures:%s !\n", paths[i]);
            return (0);
        }
        i++;
    }    
    return (1);
}
