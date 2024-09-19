/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_sep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:43:48 by likong            #+#    #+#             */
/*   Updated: 2024/09/19 13:47:03 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_sep(char *str, char *sep)
{
	int	i;

	i = 0;
	if (!str || !sep)
		return (i);
	while (str[i] && !ft_strchr(sep, str[i]))
		i++;
	return (i);
}
