/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:44:00 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/25 20:19:12 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int type_free)
{
	char	*str;
	char	*save_str;
	char	*save_s1;
	char	*save_s2;

	if (!s1 || !s2)
		return (NULL);
	str = dh_malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	save_str = str;
	save_s2 = s2;
	save_s1 = s1;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	if (type_free == FREE_S2 || type_free == FREE_ALL)
		dh_free(save_s2);
	if (type_free == FREE_S1 || type_free == FREE_ALL)
		dh_free(save_s1);
	return (save_str);
}
