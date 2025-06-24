/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:00:52 by edubois-          #+#    #+#             */
/*   Updated: 2025/06/24 16:04:25 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void    ft_array_replace(char **array, char *items, char c)
{
    static int y = 0;
    int x;

    while (array[y])
    {
        x = 0;
        while (array[y][x])
        {
            if (ft_strchr(items, array[y][x]))
                array[y][x] = c;
            x++;
        }
        y++;
    }
}