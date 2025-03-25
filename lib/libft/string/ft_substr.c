/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:19:45 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/12 14:43:51 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*save_str;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < len + start)
		len = s_len - start;
	if (start > s_len)
		len = 0;
	str = dh_malloc(len + 1);
	if (!str)
		return (NULL);
	while (start && *s++)
		start--;
	save_str = str;
	while (len--)
		*str++ = *(char *)s++;
	*str = '\0';
	return (save_str);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len, int is_free)
{
	char	*str;
	char	*save_str;
	char	*save_s;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < len + start)
		len = s_len - start;
	if (start > s_len)
		len = 0;
	str = dh_malloc(len + 1);
	if (!str)
		return (NULL);
	save_s = s;
	while (start && *s++)
		start--;
	save_str = str;
	while (len--)
		*str++ = *(char *)s++;
	*str = '\0';
	if (is_free)
		dh_free(save_s);
	return (save_str);
}
