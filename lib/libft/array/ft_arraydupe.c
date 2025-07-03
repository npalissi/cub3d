/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydupe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:32:32 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/03 01:02:20 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_arraydupe(char **tab)
{
	char	**new_tab;
	char	**save_new_tab;

	new_tab = dh_malloc((ft_arraylen(tab) + 1) * sizeof(char *));
	if (!new_tab)
		return (0);
	save_new_tab = new_tab;
	while (tab && *tab)
	{
		*new_tab = ft_strdup(*tab++);
		if (!new_tab++)
		{
			ft_free_tab(save_new_tab);
			return (0);
		}
	}
	*new_tab = 0;
	return (save_new_tab);
}
