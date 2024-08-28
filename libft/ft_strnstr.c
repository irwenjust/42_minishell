/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:21:29 by likong            #+#    #+#             */
/*   Updated: 2024/07/25 08:28:33 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	if ((!haystack || !needle) && len == 0)
		return (NULL);
	i = 0;
	needle_len = ft_strlen(needle);
	if (!needle[i])
		return ((char *)haystack);
	while (haystack[i] != '\0' && i <= len - needle_len && len > 0)
	{
		if (haystack[i] == needle[0] && needle_len <= len - i)
		{
			if (!ft_memcmp(haystack + i, needle, needle_len))
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
