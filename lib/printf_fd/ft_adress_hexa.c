/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adress_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:34:43 by edubois-          #+#    #+#             */
/*   Updated: 2024/11/29 23:13:39 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"

int	ft_adress_hexa(int fd, void *a)
{
	if (!a)
		return (ft_putstr(fd, "(nil)"));
	ft_putstr(fd, "0x");
	return (ft_putnbr_hexa(fd, (unsigned long long)a, 0) + 2);
}
