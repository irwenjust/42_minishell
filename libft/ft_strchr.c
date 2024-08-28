/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:42:51 by likong            #+#    #+#             */
/*   Updated: 2024/07/25 08:28:21 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	if (!s)
		return (NULL);
	while (i < len + 1)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
