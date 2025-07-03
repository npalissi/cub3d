/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:38:44 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/02 23:53:12 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

void	ft_print_array(char **str)
{
	int	y;

	y = 0;
	while (str[y])
	{
		printf("%s", str[y]);
		if (str[y][ft_strlen(str[y]) - 1] != '\n')
			printf("\n");
		y++;
	}
	printf("\n");
	printf("\n");
	printf("\n");
}
