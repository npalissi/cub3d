/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:51:06 by edubois-          #+#    #+#             */
/*   Updated: 2024/10/22 22:36:56 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s++ == (unsigned char)c)
			return ((char *)s - 1);
	}
	if (!(unsigned char)c)
		return ((char *)s);
	return (0);
}
