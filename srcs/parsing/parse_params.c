/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:17:04 by edubois-          #+#    #+#             */
/*   Updated: 2025/06/18 13:49:40 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int    parse_occu(char **map)
{
    static char *key_mapping[6] = {"NO", "SO", "EA", "WE", "F", "C"};
    int i;
    int error;

    i = 0;
    error = 1;
    while(i < 6)
    {
        if (count_occurrences(key_mapping[i], map) != 1)
            error = 0;
        i++;
    }
    return (error);
}
