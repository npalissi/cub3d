/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 06:39:55 by edubois-          #+#    #+#             */
/*   Updated: 2025/05/06 18:36:50 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strcmpp(char *s1, char *s2)
{
	char	*save_s1;

	save_s1 = s1;
	while (s1 && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (s1 && !*s1 && !*s2)
	{
		dh_free(save_s1);
		return (1);
	}
	return (0);
}

int	ft_strllen(char *s)
{
	int	c;

	c = 0;
	if (!s)
		return (0);
	while (*s++)
		c++;
	return (c);
}

void	*ft_memsett(void *s, int c, size_t n)
{
	void	*clone;

	if (!s)
		return (NULL);
	clone = s;
	while (n--)
		*(unsigned char *)s++ = c;
	return (clone);
}

char	*ft_char_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*save_str;
	char	*s1_tmp;

	s1_tmp = s1;
	str = dh_malloc (ft_strllen(s1) + ft_strllen(s2) + 1);
	if (!str)
		return (NULL);
	save_str = str;
	while (s1 && *s1)
		*str++ = *s1++;
	while (s2 && *s2)
		*str++ = *s2++;
	*str = '\0';
	if (s1_tmp)
		dh_free(s1_tmp);
	return (save_str);
}
