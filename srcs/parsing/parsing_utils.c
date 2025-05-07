/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:54:47 by edubois-          #+#    #+#             */
/*   Updated: 2025/05/07 12:20:14 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int len_max(char **str)
{
    int max;
    int temp;

    max = ft_strlen(*str);
    while (*str)
    {
        temp = ft_strlen(*str);
        if (temp > max)
            max = temp;
        str++;
    }
    return max;
}

int     find_y(char **map, int i)
{
    int find;
    int y;

    find = 0;
    while (map[i])
    {
        y = 0;
        while (map[i][y])
        {
            if (map[i][y] == 'N' || map[i][y] == 'S'
                || map[i][y] == 'W' || map[i][y] == 'E')
                return y;
            y++;
        }
        i++;
    }
    return (-1);
}

int find_x(char **map, int i)
{
    int y;

    while (map[i])
    {
        y = 0;
        while (map[i][y])
        {
            if (map[i][y] == 'N' || map[i][y] == 'S'
                || map[i][y] == 'W' || map[i][y] == 'E')
                return i;
            y++;
        }
        i++;
    }
    return (-1); 
}


