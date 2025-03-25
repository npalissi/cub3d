/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:55:57 by edubois-          #+#    #+#             */
/*   Updated: 2025/02/25 11:51:22 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	in_set(char s, const char *set)
{
	while (*set)
	{
		if (s == *set++)
			return (1);
	}
	return (0);
}

static size_t	get_prefix(const char *s, const char *set)
{
	size_t	i;

	i = 0;
	while (s[i] && in_set(s[i], set))
		i++;
	return (i);
}

static size_t	get_suffix(const char *s, const char *set)
{
	size_t	i;
	int		c;

	c = 0;
	if (s)
		i = ft_strlen(s);
	else
		i = -1;
	while (in_set(s[--i], set) && i)
		c++;
	return (c);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		pre_t;
	size_t		su_t;

	if (!s1)
		return (NULL);
	pre_t = get_prefix(s1, set);
	if (pre_t == ft_strlen(s1) || !s1)
		return (ft_strdup(""));
	su_t = get_suffix(s1, set);
	return (ft_substr(s1, pre_t, ft_strlen(s1) - (su_t + pre_t)));
}
