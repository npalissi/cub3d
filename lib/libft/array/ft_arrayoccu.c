/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayoccu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:41:42 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/03 00:07:55 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_arrayoccu(char **tab, int c)
{
	int	i;
	int	j;
	int	find;

	i = 0;
	find = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == c)
				find++;
			j++;
		}
		i++;
	}
	return (find);
}
