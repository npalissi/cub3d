/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:05 by edubois-          #+#    #+#             */
/*   Updated: 2025/05/12 14:14:39 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_map(char **map)
{
	for(int i = 0; map[i]; i++)
	{
		printf("%s",map[i]);
		if (map[i][ft_strlen(map[i]) - 1] != '\n')
			printf("\n");
	}
	printf("\n");
}

void print_texture(t_texture t)
{
	printf("%s\n", t.north);
	printf("%s\n", t.south);
	printf("%s\n", t.west);
	printf("%s\n", t.east);
}

void	print_color(t_color t)
{
    unsigned int f = t.floor;
    unsigned int c = t.ceiling;

    // Extraire les composantes RGB
    unsigned int fr = (f >> 16) & 0xFF;
    unsigned int fg = (f >> 8) & 0xFF;
    unsigned int fb = f & 0xFF;

    unsigned int cr = (c >> 16) & 0xFF;
    unsigned int cg = (c >> 8) & 0xFF;
    unsigned int cb = c & 0xFF;

    // ANSI 24-bit : \033[38;2;<r>;<g>;<b>m
    printf("Floor: \033[38;2;%u;%u;%um%06X\033[0m | ", fr, fg, fb, f);
    printf("Ceiling: \033[38;2;%u;%u;%um%06X\033[0m\n", cr, cg, cb, c);
}

int main(int argc, char **argv)
{
	t_game game;

	if (argc != 2 || !get_map(argv[1], &game) || !get_textures(&game) || !get_colors(&game))
	{
		if (argc !=2)
			ft_printf(2, "Need 1 file name as argument\n");
		return (1);
	}
	cut_map(&game);
	print_map(game.map.map);
	print_texture(game.texture);
	print_color(game.color);
}
