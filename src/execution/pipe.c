/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:10:01 by likong            #+#    #+#             */
/*   Updated: 2024/09/09 12:28:05 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(void)
{
	int	i;

	(ms()->fds) = ft_calloc(ms()->cmd_nb, sizeof(int *));
	if (!ms()->fds)
		return ;
	i = -1;
	while (++i < (ms()->cmd_nb) - 1)
	{
		(ms()->fds[i]) = ft_calloc(2, sizeof(int));
		if (!ms()->fds[i])
		{
			matrix_delete(ms()->fds);
			return ;
		}
		pipe(ms()->fds[i]);
	}
}
