/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:10:01 by likong            #+#    #+#             */
/*   Updated: 2024/09/18 19:04:48 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(void)
{
	int	i;

	// printf("cmd_num: %d\n", ms()->cmd_nb);
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
		// printf("i: %d, fd[0]: %d, fd[1]: %d\n", i, ms()->fds[i][0], ms()->fds[i][1]);
	}
}
