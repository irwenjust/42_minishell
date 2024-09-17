/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:59:03 by likong            #+#    #+#             */
/*   Updated: 2024/09/17 14:17:52 by likong           ###   ########.fr       */
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

bool	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd"));
}

// Some doubts for export command
bool	is_unfork(char *cmd, char *arg)
{
	return (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "exit")
		|| (!ft_strcmp(cmd, "export") && arg)
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "pwd"));
}
