/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:15:27 by edubois-          #+#    #+#             */
/*   Updated: 2024/11/30 19:33:29 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *s, int *over)
{
	int		sign;
	long	number;

	*over = 0;
	while (((*s >= 9 && *s <= 13) || (*s == ' ')) && (*s))
		s++;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	number = 0;
	while (*s >= '0' && *s <= '9' && *s)
	{
		number = number * 10 + *s - '0';
		if (number * sign > 2147483647 || number * sign < -2147483648)
			*over = 1;
		s++;
	}
	return (number * sign);
}
