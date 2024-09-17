/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:21:17 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/17 13:56:01 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(void)
{
	int	i;

	i = -1;
	if (!find_env(ms()->env_list, "PATH"))
		return ;
	while (ms()->envp[++i])
		printf("%s\n", ms()->envp[i]);
	ms()->exit = 0;
}
