/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:20:14 by likong            #+#    #+#             */
/*   Updated: 2024/08/29 14:27:32 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_len(char *str, char *sep)
{
	int	i;

	i = 0;
	while (str[i] && !ft_strchr(sep, str[i]))
		i++;
	return (i);
}

int	error_info(char *info)
{
	if (info)
		printf("%s\n", info);
	return (0);
}
