/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 07:25:40 by edubois-          #+#    #+#             */
/*   Updated: 2024/11/29 23:12:17 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	send_args(int fd, char *av, va_list lst)
{
	if (*av == '%' && *av++ && ft_strchr("cspduixX%", *av))
	{
		if (*av == 'c')
			return (ft_putchar(1, va_arg(lst, int)));
		if (*av == 's')
			return (ft_putstr(1, va_arg(lst, char *)));
		if (*av == 'p')
			return (ft_adress_hexa(1, va_arg(lst, void *)));
		if (*av == 'd' || *av == 'i')
			return (ft_putnbr(1, va_arg(lst, int)));
		if (*av == 'u')
			return (ft_putnbr_unsigned(1, va_arg(lst, unsigned int)));
		if (*av == 'x')
			return (ft_putnbr_hexa(1, va_arg(lst, unsigned int), 0));
		if (*av == 'X')
			return (ft_putnbr_hexa(1, va_arg(lst, unsigned int), 1));
		if (*av == '%')
			return (write(fd, "%", 1));
	}
	return (-1);
}

static int	abs(int c)
{
	return (c * ((c > 0) - (c < 0)));
}

int	ft_printf(int fd, const char *argv, ...)
{
	int		len;
	int		result;
	va_list	lst;
	char	*av;

	if (!argv)
		return (-1);
	len = 0;
	result = 0;
	va_start(lst, argv);
	av = (char *)argv;
	while (*av)
	{
		result = send_args(fd, av, lst);
		if (result == -1)
			write (fd, av, 1);
		else
			av++;
		len += abs(result);
		av++;
	}
	va_end(lst);
	return (len);
}
