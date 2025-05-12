/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:14:18 by edubois-          #+#    #+#             */
/*   Updated: 2025/05/12 14:45:02 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int    fill_color(t_game *game, int i)
{
    int overflow;

    overflow = 0;
    if (i == 1)
        game->color.floor = rgba_to_hex(ft_substr(*game->map.map, 2,
            ft_strlen(*game->map.map) - 3), &overflow);
    else
        game->color.ceiling = rgba_to_hex(ft_substr(*game->map.map, 2,
            ft_strlen(*game->map.map) - 3), &overflow);
    if (overflow == 1)
        ft_printf(2, "Error, color have to be between 0 and 255 for rgb !\n");
    if (ft_charite(*game->map.map, ',') != 2 || overflow == 2)
    {
        ft_printf(2, "Error, color have to be under rgb type (R,G,B)\n");
        overflow = 1;
    }
    return (overflow != 1);
}

int get_colors(t_game *game)
{
    char **save_map;
    char *co[2] = {"C ", "F "};
    int i;
    
    i = 0;
    save_map = game->map.map;
    while (i < 2)
    {
        game->map.map = save_map;
        while (!ft_strcmp(ft_substr(*game->map.map, 0, 2), co[i]) && *game->map.map)
            game->map.map++;
        if (*game->map.map)
        {
            if (!fill_color(game, i))
                return (0);
            i++;
        }
        else
        {
            ft_printf(2, "Error, Not all color codes are there ! Missing at least: %s\n", co[i]);
            return (0);
        }
    }
    return (1);
}
