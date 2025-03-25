/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:55:48 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/25 19:21:52 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*save_start;
	const char	*save_little;

	if (ft_strlen(little) && !len)
		return (NULL);
	if (!len || !ft_strlen(little))
		return ((char *)big);
	save_little = little;
	if (!*little)
		return ((char *)big);
	while (*big && ft_strlen(little) <= len && len && len--)
	{
		if (*big == *little)
		{
			save_start = big;
			if (!ft_memcmp(big, little, ft_strlen(little)))
				return ((char *)save_start);
		}
		little = save_little;
		big++;
	}
	return (NULL);
}

char	*ft_strstr(const char *big, const char *little)
{
	const char	*save_start;
	const char	*save_little;

	if (!ft_strlen(little))
		return ((char *)big);
	save_little = little;
	if (!*little)
		return ((char *)big);
	while (*big)
	{
		if (*big == *little)
		{
			save_start = big;
			if (!ft_memcmp(big, little, ft_strlen(little)))
				return ((char *)save_start);
		}
		little = save_little;
		big++;
	}
	return (NULL);
}
