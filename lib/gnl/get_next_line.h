/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:31:59 by edubois-          #+#    #+#             */
/*   Updated: 2025/05/06 18:31:06 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

char	*get_next_line(int fd);
int		ft_strcmpp(char *s1, char *s2);
int		ft_strllen(char *s);
void	*ft_memsett(void *s, int c, size_t n);
char	*ft_char_strjoin(char *s1, char *s2);

#endif