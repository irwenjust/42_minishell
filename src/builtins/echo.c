/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:51:42 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/05 15:56:23 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **token)
{
	int	i;

	i = 0;
	if (token[0] && !ft_strcmp(token[0], "-n"))
		i++;
	while (token[i])
	{
		printf("%s", token[i]);
		i++;
		if (token[i])
			printf(" ");
	}
	if (!token[0] || ft_strcmp(token[0], "-n") != 0)
		printf("\n");
}
