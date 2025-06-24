/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/06/24 18:30:48 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

int get_max_map_width(char **map)
{
    int max = 0;
    int i = 0;
    while (map[i])
    {
        int len = ft_strlen(map[i]);
        if (len > max)
            max = len;
        i++;
    }
    return max;
}

void put_item(t_game *game, char item)
{
    int x, y;

    int map_height = ft_arraylen(game->mini.map);
    int map_width = get_max_map_width(game->mini.map);

    int minimap_width = map_width * TILE_SIZE;
    int minimap_height = map_height * TILE_SIZE;

    int offset_x = (WIDTH - minimap_width) / 2;
    int offset_y = (HEIGHT - minimap_height) / 2;

    for (y = 0; y < map_height; y++)
    {
        int row_len = ft_strlen(game->mini.map[y]);
        for (x = 0; x < row_len; x++)
        {
            if (item == game->mini.map[y][x] && item == '0')
                mlx_pixel_put_region(game->mlx, game->win, offset_x + x * TILE_SIZE, offset_y + y * TILE_SIZE, 25, 25, game->mini.b);
            if (item == game->mini.map[y][x] && item == '1')
                mlx_pixel_put_region(game->mlx, game->win, offset_x + x * TILE_SIZE, offset_y + y * TILE_SIZE, 25, 25, game->mini.w);

        }
    }
}
void draw_minimap(t_game *game)
{
    put_item(game, '0');
    put_item(game, '1');

    int map_height = ft_arraylen(game->mini.map);
    int map_width = get_max_map_width(game->mini.map);

    int minimap_width = map_width * TILE_SIZE;
    int minimap_height = map_height * TILE_SIZE;

    int offset_x = (WIDTH - minimap_width) / 2;
    int offset_y = (HEIGHT - minimap_height) / 2;

    int player_tile_x = (int)(game->player.x / BLOCK_SIZE);
    int player_tile_y = (int)(game->player.y / BLOCK_SIZE);

    mlx_put_image_to_window(game->mlx, game->win, game->mini.back,  offset_x + player_tile_x * TILE_SIZE, offset_y + player_tile_y * TILE_SIZE);
    mlx_pixel_put_region(game->mlx, game->win, offset_x + player_tile_x * TILE_SIZE, offset_y + player_tile_y * TILE_SIZE, 25, 25, game->mini.c);
}