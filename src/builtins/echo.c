/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:51:42 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/17 13:58:01 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **token)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	// printf("key: %s\n", token[1]);
	if (token[1] && !ft_strcmp(token[1], "-n"))
	{
		flag = 1;
		i++;
	}
	while (token[i])
	{
		printf("%s", token[i]);
		i++;
		if (token[i])
			printf(" ");
	}
	if (!token[1] || flag == 0)
		printf("\n");
	ms()->exit = 0;
}
