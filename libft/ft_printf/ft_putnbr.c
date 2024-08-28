/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:06:21 by likong            #+#    #+#             */
/*   Updated: 2024/07/25 08:31:50 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int		len;
	long	num;

	num = n;
	len = 0;
	if (num < 0 && ++len)
	{
		num = -num;
		if (write(1, "-", 1) == -1)
			return (-1);
	}
	if (num >= 10)
	{
		len += ft_putnbr((int)(num / 10));
		if (len == -1)
			return (-1);
		num = num % 10;
	}
	if (num <= 9)
	{
		if (ft_putchar(('0' + num)) == -1)
			return (-1);
		len++;
	}
	return (len);
}
