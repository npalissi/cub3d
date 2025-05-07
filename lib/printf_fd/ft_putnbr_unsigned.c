/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:32:58 by edubois-          #+#    #+#             */
/*   Updated: 2024/11/29 23:11:30 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsigned(int fd, unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
		len += ft_putnbr_unsigned(fd, n / 10);
	len += ft_putchar(fd, n % 10 + '0');
	return (len);
}
