/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:42:03 by likong            #+#    #+#             */
/*   Updated: 2024/07/25 08:28:26 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len_o;

	i = 0;
	dst_len_o = ft_strlen(dst);
	if (dst_len_o >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (src[i] != '\0' && i + dst_len_o < dstsize - 1)
	{
		dst[i + dst_len_o] = src[i];
		i++;
	}
	dst[i + dst_len_o] = '\0';
	return (ft_strlen(src) + dst_len_o);
}
