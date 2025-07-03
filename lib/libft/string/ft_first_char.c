/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:35:10 by edubois-          #+#    #+#             */
/*   Updated: 2025/07/02 23:49:57 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	first_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && ft_iswhitespace(str[i]))
		i++;
	return (str[i] == c);
}
