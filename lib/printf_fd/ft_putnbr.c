/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:33:17 by edubois-          #+#    #+#             */
/*   Updated: 2024/11/29 23:11:14 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int fd, int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	else
	{
		if (n < 0)
		{
			n = -n;
			len += ft_putchar(fd, '-');
		}
		if (n > 9)
			len += ft_putnbr(fd, n / 10);
		len += ft_putchar(fd, n % 10 + '0');
	}
	return (len);
}
