/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:17:04 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/02 22:06:57 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int    parse_occu(char **map)
{
    static char *key_mapping[6] = {"NO", "SO", "EA", "WE", "F", "C", "DO"};
    int i;
    int error;

    i = 0;
    error = 1;
    while(i < 7)
    {
        if (count_occurrences(key_mapping[i], map) != 1)
            error = 0;
        i++;
    }
    return (error);
}
