/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:15:56 by likong            #+#    #+#             */
/*   Updated: 2024/07/25 08:27:42 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_space;
	void	*point;

	total_space = count * size;
	if (count > 0 && size > 0 && ((total_space / count) != size))
		return (NULL);
	point = malloc(total_space);
	if (!point)
		return (NULL);
	ft_bzero(point, total_space);
	return (point);
}
