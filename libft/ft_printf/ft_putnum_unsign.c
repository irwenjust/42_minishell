/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum_unsign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:46:21 by likong            #+#    #+#             */
/*   Updated: 2024/07/25 08:31:51 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnum_unsign(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
	{
		len = ft_putnum_unsign(n / 10);
		if (len == -1)
			return (-1);
		n = n % 10;
	}
	if (n <= 9)
	{
		if (ft_putchar (('0' + n)) == -1)
			return (-1);
		len++;
	}
	return (len);
}
