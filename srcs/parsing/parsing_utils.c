/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:54:47 by edubois-          #+#    #+#             */
/*   Updated: 2025/06/18 12:15:18 by edubois-         ###   ########.fr       */
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


char *concat_map(char **map)
{
    size_t total_len;
    size_t len;
    int i = 0;
    char *result;
    char *ptr;

    total_len = 0;
    while (map[i])
        total_len += ft_strlen(map[i++]);
    result = malloc(total_len + 1);
    if (!result)
        return NULL;
    ptr = result;
    i = 0;
    while (map[i])
    {
        len = ft_strlen(map[i]);
        ft_memcpy(ptr, map[i], len);
        ptr += len;
        i++;
    }
    *ptr = '\0';
    return result;
}

int find_char(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    if (str[i])
        return (i);
    return (-1);
}

int count_occurrences(char *key, char **m)
{
    char **key_mapping;
    char *map;
    char *pos;
    int count;

    size_t key_len;
    count = 0;
    map = concat_map(m);
    if (!map)
        return 0;
    key_mapping = NULL;
    key_len = ft_strlen(key);
    pos = ft_strstr(map, key);
    while (pos != NULL)
    {
        count++;
        ft_strapp(&key_mapping, ft_substr(pos, 0, find_char(pos, '\n')));
        pos = ft_strstr(pos + key_len, key);
    }
    if (ft_arraylen(key_mapping) != 1)
        custom_occu_print(key, key_mapping);
    ft_free_tab(key_mapping);
    free(map);
    return (count);
}



