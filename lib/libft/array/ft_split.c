/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:42:05 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/12 14:43:51 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	count_word(char *str, char c)
{
	int	nb_word;
	int	i;

	i = 0;
	nb_word = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		while (str[i] && str[i] != c)
			i++;
		if (str[i - 1] && str[i - 1] != c)
			nb_word++;
	}
	return (nb_word);
}

static int	next_word(char *s, int i, char c)
{
	int	skip;

	skip = 0 ;
	s += i;
	while (*s && *s == c)
	{
		s++;
		skip++;
	}
	if (!*s)
		return (0);
	return (skip);
}

static size_t	word_len(char *s, int i, char c)
{
	size_t	len;

	len = 0;
	while (s[i] && s[i++] != c)
		len++;
	return (len);
}

static char	**empty(char **tab, const char *s, int i, char c)
{
	int	j;

	if (!tab)
	{
		s += i;
		while (*s)
		{
			if (*s++ != c)
				return (NULL);
		}
		return ((char **)1);
	}
	j = 0;
	while (tab[j])
		dh_free(tab[j++]);
	dh_free(tab);
	return (0);
}

char	**ft_split(char const *str, char c)
{
	char	**table;
	int		i[3];
	char	*word;

	if (!str)
		return (NULL);
	table = dh_malloc(sizeof(char *) * (count_word((char *)str, c) + 1));
	if (!table)
		return (NULL);
	i[1] = 0;
	i[0] = 0;
	while (str[i[0]] && !empty(0, str, i[0], c))
	{
		i[2] = 0;
		i[0] += next_word((char *)str, i[0], c);
		word = dh_malloc(word_len((char *)str, i[0], c) + 1);
		if (!word)
			return (empty(table, 0, 0, 0));
		while (str[i[0]] != c && str[i[0]])
			word[i[2]++] = str[i[0]++];
		word[i[2]] = '\0';
		table[i[1]++] = word;
	}
	table[i[1]] = NULL;
	return (table);
}
