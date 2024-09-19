/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:59:03 by likong            #+#    #+#             */
/*   Updated: 2024/09/19 11:54:34 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_command(char **cmds)
{
	int	status;

	status = 0;
	if (!is_builtin(cmds[0]))
		status = exec_others(cmds);
	if (!ft_strcmp(cmds[0], "pwd"))
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp(cmds[0], "cd"))
		ft_cd(cmds);
	else if (!ft_strcmp(cmds[0], "echo"))
		ft_echo(cmds);
	else if (!ft_strcmp(cmds[0], "env") && matrix_size(cmds) == 1)
		ft_env();
	else if (!ft_strcmp(cmds[0], "exit") && ms()->cmd_nb == 1)
		ft_exit(cmds);
	else if (!ft_strcmp(cmds[0], "export"))
		ft_export(cmds);
	else if (!ft_strcmp(cmds[0], "unset"))
		ft_unset(cmds);
	return (status);
}

void	close_all(void)
{
	size_t	i;

	i = 0;
	if (ms()->in_fd > STD_IN)
		close(ms()->in_fd);
	if (ms()->out_fd > STD_OUT)
		close(ms()->out_fd);
	while (i < matrix_size((char **)ms()->fds))
	{
		if (ms()->fds[i][0] >= 0)
			close(ms()->fds[i][0]);
		if (ms()->fds[i][1] >= 0)
			close(ms()->fds[i][1]);
		i++;
	}
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
