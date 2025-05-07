/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 06:39:26 by edubois-          #+#    #+#             */
/*   Updated: 2025/05/06 18:36:50 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*cut_at_next_line(char *line)
{
	while (line && *line && *line != '\n')
		line++;
	if (line && *line)
		return (++line);
	return (NULL);
}

void	delete_old_line(char *line, char *buf)
{
	line = cut_at_next_line(line);
	while (line && *line)
	{
		*buf++ = *line;
		*line++ = '\0';
	}
	*buf = '\0';
}

char	*get_following_line(int fd, char *buf, char *line)
{
	int	b;

	b = 1;
	while (b > 0)
	{
		if (cut_at_next_line(line))
			break ;
		ft_memsett(buf, 0, BUFFER_SIZE);
		b = read(fd, buf, BUFFER_SIZE);
		line = ft_char_strjoin(line, buf);
		if (!line || ft_strcmpp(line, ""))
			return (NULL);
	}
	if (b == -1)
	{
		dh_free(line);
		return (NULL);
	}
	if (!b)
	{
		buf = NULL;
		return (line);
	}
	delete_old_line(line, buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[1024][BUFFER_SIZE + 1] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (ft_strllen(buf[fd]))
	{
		line = ft_char_strjoin(line, buf[fd]);
		if (!line)
			return (NULL);
	}
	return (get_following_line(fd, buf[fd], line));
}
