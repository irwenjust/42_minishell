/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_sep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:18:52 by likong            #+#    #+#             */
/*   Updated: 2024/09/16 13:23:07 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strchr_sep(char *s, int c, char sep)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	if (!s)
		return (false);
	while (i < len + 1 && ((unsigned char *)s)[i] != (unsigned char)sep)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (false);
		i++;
	}
	return (true);
}
