/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:02:06 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/25 19:53:31 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <errno.h>
#include <string.h>


t_buffer *new_buffer(t_buffer **lst)
{
	t_buffer *node;
	t_buffer *tmp;
	
	node = malloc(sizeof(t_buffer ));
	node->next = NULL;
	if (!node)
		return (0);
	tmp = *lst;
	if (!*lst)
		*lst = node;
	else
	{
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = node; 
	}
	return (node);
}

t_buffer *read_file(int fd, t_buffer **lst)
{
	t_buffer *node;
	int size;
	int size_read;

	node = new_buffer(lst);
	if(!node)
		return (0);
	size = sizeof(node->buffer);
	size_read = read(fd, node->buffer, size);
	if (size_read != size)
		return (*lst);
	return (read_file(fd, lst));
}

char *join_buffer(t_buffer *lst)
{
	t_buffer *tmp;
	char *map;

	tmp = lst;
	if (!tmp)
		return (0);
	map = ft_strdup(tmp->buffer);
	if (!map)
		return (0);
	while(tmp)
	{
		map = ft_strjoinfree(map, tmp->buffer, FREE_S1);
		tmp = tmp->next;
	}
	return (map);
}

char *recover_file(t_game *game, char *name_file)
{
	int fd;
	char *map;

	fd = open(name_file, O_RDONLY);
	game->lst_buffer = NULL;
	if (fd == -1)
		return (0);
	read_file(fd, &game->lst_buffer);
	close(fd);
	map = join_buffer(game->lst_buffer);
	return (map);
}
