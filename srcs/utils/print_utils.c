/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:38:08 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/02 21:56:53 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void   custom_occu_print(char *key, char **map)
{
    int i;

    i = 0;
    ft_printf(2, "Error, %s defined %d time !\n", key, ft_arraylen(map));
    while (map && map[i])
    {
        if (!i)
            printf(GREEN "%s" RESET"%s\n", ft_substr(map[i], 0, ft_strlen(key)), ft_substr(map[i], ft_strlen(key), ft_strlen(map[i])));
        else
            printf(RED "%s" RESET"%s\n", ft_substr(map[i], 0, ft_strlen(key)), ft_substr(map[i], ft_strlen(key), ft_strlen(map[i])));
        i++;
    }
}