/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:05 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 03:22:07 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

int	is_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	return (str[i] == '\0');
}

int	match_key(t_game *game, char *str)
{
	if (ft_strstr(str, game->color.cl)
		|| ft_strstr(str, game->color.fl)
		|| ft_strstr(str, game->texture.north)
		|| ft_strstr(str, game->texture.south)
		|| ft_strstr(str, game->texture.east)
		|| ft_strstr(str, game->texture.west))
		return (1);
	return (0);
}

int    check_full_map(t_game *game)
{
    char    *str;
    int        empty[2];

    empty[1] = 0;
    while (*game->map.full_map)
    {
        empty[0] = 1;
        str = *game->map.full_map++;
        empty[0] = is_empty_line(str);
        if (!empty[0])
        {
            --game->skipped;
            if (!game->skipped)
                break ;
            if (match_key(game, str))
                continue ;
            else
                empty[1] += ft_printf(2, "Error, files must be clean,"
                        RED"%s\n"RESET, str);
        }
    }
    return (empty[1]);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game = (t_game){0};
	if (argc != 2)
	{
		ft_printf(2, "Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (!get_map(argv[1], &game) || !get_textures(&game)
		|| !get_colors(&game) || !cut_map(&game))
		return (1);
	if (!init_mlx(&game))
		return (1);
	if (!load_textures(&game) || check_full_map(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	load_map_data(&game);
	init_frame_buffer(&game);
	init_game(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
