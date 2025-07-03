/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:27:47 by edubois-          #+#    #+#             */
/*   Updated: 2025/05/06 18:42:19 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_tab(char **tab)
{
	char	**tmp;

	if (!tab)
		return ;
	tmp = tab;
	while (*tmp)
		dh_free(*tmp++);
	dh_free(tab);
}
