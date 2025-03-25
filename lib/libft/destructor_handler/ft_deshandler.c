/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deshandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:44:40 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/18 12:39:42 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

t_list	*dh_get_heap(t_list *lst)
{
	static t_list	*lst_heap;

	if (lst)
		lst_heap = lst;
	if (!lst && !lst_heap)
		return (NULL);
	return (lst_heap);
}

int	dh_add_ptr(void *ptr)
{
	t_list	*new_node;
	t_list	*lst;

	lst = dh_get_heap(NULL);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->next = NULL;
	new_node->content = ptr;
	if (lst)
		new_node->next = lst;
	lst = new_node;
	dh_get_heap(lst);
	return (1);
}

void	dh_free_all(void)
{
	t_list	*lst;
	t_list	*tmp;

	lst = dh_get_heap(NULL);
	while (lst)
	{
		tmp = lst->next;
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	dh_free(void *ptr)
{
	t_list	*lst;
	t_list	*tmp;

	lst = dh_get_heap(NULL);
	tmp = lst;
	while (tmp)
	{
		if (tmp->content == ptr)
		{
			free(tmp->content);
			tmp->content = NULL;
			break ;
		}
		tmp = tmp->next;
	}
	dh_get_heap(lst);
}

void	*dh_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!dh_add_ptr(ptr))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
