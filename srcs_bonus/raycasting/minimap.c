/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 12:43:41 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"

void	draw_tile(t_game *game, t_vec2 pos, char item, t_minimap_config config)
{
	t_vec2	screen_pos;

	screen_pos.x = config.offset.x + pos.x * TILE_SIZE;
	screen_pos.y = config.offset.y + pos.y * TILE_SIZE;
	if (item == '0' || item == ' ')
		mlx_put_image_to_window(game->mlx, game->win, game->mini.back,
			screen_pos.x, screen_pos.y);
	else if (item == '1' || item == 'D')
		mlx_put_image_to_window(game->mlx, game->win, game->mini.wall,
			screen_pos.x, screen_pos.y);
}

bool	should_draw_tile(char map_char, char target_item, bool wall_seen)
{
	if (map_char != target_item)
		return (false);
	if (target_item == '0' || (target_item == ' ' && wall_seen))
		return (true);
	if (target_item == '1' || target_item == 'D')
		return (true);
	return (false);
}

void	put_item(t_game *game, char item)
{
	t_minimap_config	config;
	t_vec2				pos;
	bool				wall_seen;
	int					row_len;

	config = get_minimap_config(game);
	pos.y = 0;
	while (pos.y < config.map_size.y)
	{
		row_len = ft_strlen(game->mini.map[pos.y]);
		wall_seen = false;
		pos.x = 0;
		while (pos.x < row_len)
		{
			if (game->mini.map[pos.y][pos.x] == '1')
				wall_seen = true;
			if (should_draw_tile(game->mini.map[pos.y][pos.x], item, wall_seen))
				draw_tile(game, pos, item, config);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_player_on_minimap(t_game *game, t_minimap_config config)
{
	t_vec2	player_pos;
	t_vec2	final_pos;
	int		player_size;

	player_pos.x = (game->player.x / BLOCK_SIZE) * TILE_SIZE;
	player_pos.y = (game->player.y / BLOCK_SIZE) * TILE_SIZE;
	final_pos.x = config.offset.x + player_pos.x;
	final_pos.y = config.offset.y + player_pos.y;
	player_size = 25;
	final_pos.x -= player_size / 2;
	final_pos.y -= player_size / 2;
	mlx_pixel_put_region(game->mlx, game->win, final_pos.x, final_pos.y,
		player_size, player_size, game->mini.c);
}

void	draw_minimap(t_game *game)
{
	t_minimap_config	config;

	put_item(game, '0');
	put_item(game, ' ');
	put_item(game, '1');
	put_item(game, 'D');
	config = get_minimap_config(game);
	draw_player_on_minimap(game, config);
}
