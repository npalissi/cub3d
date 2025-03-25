/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:44:48 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/12 14:43:42 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	nb_len(int n)
{
	int				c;
	unsigned int	nb_max;

	c = 0;
	if (n < 0)
		nb_max = -n;
	else
		nb_max = n;
	if (!n)
		return (1);
	while (nb_max > 0)
	{
		nb_max /= 10;
		c++;
	}
	return (c);
}

static char	*fill_buffer(char *nb, int n)
{
	int				i;
	unsigned int	nb_max;

	if (n < 10 && n >= 0)
		i = 1;
	i = nb_len(n) + (n < 0);
	nb[i--] = '\0';
	if (n < 0)
	{
		nb_max = -n;
		nb[0] = '-';
	}
	else
		nb_max = n;
	while (nb_max > 9)
	{
		nb[i--] = (nb_max % 10) + '0';
		nb_max /= 10;
	}
	nb[i--] = nb_max + '0';
	return (nb);
}

char	*ft_itoa(int n)
{
	char	*nb;

	nb = dh_malloc(nb_len(n) + 1 + (n < 0));
	if (!nb)
		return (NULL);
	fill_buffer(nb, n);
	return (nb);
}
