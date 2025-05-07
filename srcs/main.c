/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:04:05 by edubois-          #+#    #+#             */
/*   Updated: 2025/05/07 15:05:55 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **map)
{
	for(int i = 0; map[i]; i++)
		printf("%s",map[i]);
	printf("\n");
}

#include <string.h>

int main(int argc, char **argv)
{
	char **map;
	int *fd;
	
	map = NULL;
	fd = NULL;
	if (argc != 2 || !get_map(argv[1], &map) || !get_textures(&map , fd))
	{
		if (argc !=2)
			ft_printf(2, "Need 1 file name as argument\n");
		return (1);
	}
	// for (int k = 0; fd[k]; k++)
		// printf("%d\n", fd[k]);
	ft_free_tab(map);
}