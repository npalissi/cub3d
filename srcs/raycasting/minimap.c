/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/01 11:24:58 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

int get_max_map_width(char **map) {
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

void put_item(t_game *game, char item) {
    int x, y;
    bool wall_seen;
    int map_height = ft_arraylen(game->mini.map);
    int map_width = get_max_map_width(game->mini.map);
    
    int minimap_width = map_width * TILE_SIZE;
    int minimap_height = map_height * TILE_SIZE;
    
    int offset_x = (WIDTH - minimap_width) / 2;
    int offset_y = (HEIGHT - minimap_height) / 2;
    
    
    for (y = 0; y < map_height; y++)
    {
        int row_len = ft_strlen(game->mini.map[y]);
        wall_seen = false;
        for (x = 0; x < row_len; x++)
        {
            if (game->mini.map[y][x] == '1')
                wall_seen = true;
            if (item == game->mini.map[y][x] && (item == '0' || ((item == ' ') && wall_seen)))
                mlx_put_image_to_window(game->mlx, game->win, game->mini.back, offset_x + x * TILE_SIZE, offset_y + y * TILE_SIZE);
            if (item == game->mini.map[y][x] && (item == '1' || item == 'D'))
                mlx_put_image_to_window(game->mlx, game->win, game->mini.wall, offset_x + x * TILE_SIZE, offset_y + y * TILE_SIZE);
        }
    }
}

void draw_minimap(t_game *game) {
    put_item(game, '0');
    put_item(game, ' ');
    put_item(game, '1');
    put_item(game, 'D');
    int map_height = ft_arraylen(game->mini.map);
    int map_width = get_max_map_width(game->mini.map);
    
    int minimap_width = map_width * TILE_SIZE;
    int minimap_height = map_height * TILE_SIZE;
    
    int offset_x = (WIDTH - minimap_width) / 2;
    int offset_y = (HEIGHT - minimap_height) / 2;
    
    float player_minimap_x = (game->player.x / BLOCK_SIZE) * TILE_SIZE;
    float player_minimap_y = (game->player.y / BLOCK_SIZE) * TILE_SIZE;
    
    // Position finale avec les offsets de centrage
    int final_x = offset_x + (int)player_minimap_x;
    int final_y = offset_y + (int)player_minimap_y;
    
    // Taille du point joueur (plus petit pour un rendu plus précis)
    int player_size = 25; // ou une valeur fixe comme 8
    
    // Centrer le point sur la position calculée
    final_x -= player_size / 2;
    final_y -= player_size / 2;
    
    // Dessiner le joueur à sa position fluide
    mlx_pixel_put_region(game->mlx, game->win, final_x, final_y, player_size, player_size, game->mini.c);
}