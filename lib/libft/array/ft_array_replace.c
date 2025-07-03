/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:00:52 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/02 23:59:17 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_array_replace(char **array, char *items, char c)
{
	static int	y = 0;
	int			x;

	if (!array)
		return ;
	while (array[y])
	{
		x = 0;
		while (array[y][x])
		{
			if (ft_strchr(items, array[y][x]))
				array[y][x] = c;
			x++;
		}
		y++;
	}
}
