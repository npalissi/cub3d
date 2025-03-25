/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:59:31 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/12 14:43:51 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_strapp(char ***tab, char *str)
{
	char	**tmp;
	char	**save_tab;
	int		i;

	if (tab)
		save_tab = *tab;
	tmp = ft_calloc((ft_arraylen(*tab) + 2), sizeof(char *));
	if (!tmp)
		return ;
	i = 0;
	while (save_tab && save_tab[i])
	{
		tmp[i] = save_tab[i];
		i++;
	}
	tmp[i] = str;
	dh_free(*tab);
	*tab = tmp;
}
