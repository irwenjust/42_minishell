/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:10:01 by likong            #+#    #+#             */
/*   Updated: 2024/09/19 12:03:33 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_fd(void)
{
	if (ms()->in_fd >= STD_IN)
		if (dup2(ms()->in_fd, STD_IN) == -1)
			ft_err(NULL, DUP2, FAIL_STD);
	if (ms()->out_fd >= STD_OUT)
		if (dup2(ms()->out_fd, STD_OUT) == -1)
			ft_err(NULL, DUP2, FAIL_STD);
}

void	apply_fd(int index)
{
	if (ms()->cmd_nb < 2)
		return ;
	if (ms()->in_fd == STD_IN)
		if (index != 0)
			ms()->in_fd = ms()->fds[index - 1][READ];
	if (ms()->out_fd == STD_OUT)
		if (index < ms()->cmd_nb - 1)
			ms()->out_fd = ms()->fds[index][WRITE];
}

void	close_fd(int command_index)
{
	if (ms()->in_fd > STD_IN)
		close(ms()->in_fd);
	if (ms()->out_fd > STD_OUT)
		close(ms()->out_fd);
	if (command_index > 0)
		close(ms()->fds[command_index - 1][READ]);
	if (command_index < ms()->cmd_nb - 1)
		close(ms()->fds[command_index][WRITE]);
	ms()->in_fd = STD_IN;
	ms()->out_fd = STD_OUT;
}

pid_t	not_pipe(t_ast *node, pid_t pid)
{
	if (is_unfork(node->arg[0], node->arg[1]))
		handle_command(node->arg);
	else if (!is_pipe(node->token) && node->token->type != TK_LOC_V)
		pid = handle_child_process(node);
	return (pid);
}

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
