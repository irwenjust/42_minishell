/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:44:05 by likong            #+#    #+#             */
/*   Updated: 2024/09/19 13:18:34 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Might need change later
int	exec_others(char **cmds)
{
	int			status;
	char		*path;
	struct stat	path_stat;

	status = 0;
	if (!ft_strcmp(cmds[0], "="))
	{
		status = ft_err(cmds[0], COMMAND, FAIL_FCMD);
		return (status);
	}
	path = get_path(cmds[0]);
	stat(path, &path_stat);
	if (path)
	{
		status = path_error(path_stat, path, status, cmds);
		ft_free(path);
	}
	else if (ft_strchr(cmds[0], '/'))
		status = ft_err(cmds[0], FILE_NAME, FAIL_FCMD);
	else if (ft_strlen(cmds[0]) >= 1)
		status = ft_err(cmds[0], COMMAND, FAIL_FCMD);
	return (status);
}

int	exec_re(t_ast *node)
{
	int	status;

	status = 0;
	if (!node)
		return (status);
	status = exec_re(node->left);
	if (ms()->in_fd == -1 || ms()->out_fd == -1)
		restart(true);
	if (is_redir(node->token) && node->arg[0])
	{
		redirect(node->token->type, node->arg[0]);
		return (status);
	}
	apply_fd(node->index);
	dup_fd();
	close_all();
	status = handle_command(node->arg);
	return (status);
}

pid_t	handle_child_process(t_ast *node)
{
	pid_t	pid;

	signal_child();
	pid = fork();
	if (pid < 0)
		ft_err(NULL, FORK, FAIL_STD);
	else if (pid == 0)
	{
		exec_re(node);
		restart(true);
	}
	close_fd(node->index);
	return (pid);
}

static pid_t	fill_pipe(t_ast *node, pid_t pid)
{
	while (node)
	{
		if (is_pipe(node->token))
		{
			pid = handle_child_process(node->right);
			if (ms()->last_pid == 0)
				ms()->last_pid = pid;
			if (!is_pipe(node->left->token))
			{
				if (!ft_strcmp(node->left->arg[0], "exit") && ms()->cmd_nb == 1)
					handle_command(node->left->arg);
				else if (node->left->token->type != TK_LOC_V)
					pid = handle_child_process(node->left);
				break ;
			}
		}
		else if (node->token->type != TK_LOC_V && node->token->tk != NULL)
		{
			pid = not_pipe(node, pid);
			break ;
		}
		node = node->left;
	}
	return (pid);
}

//missed signal function
void	execute(t_ast *ast)
{
	pid_t	pid;
	int		status;

	status = 0x7F;
	pid = 0;
	create_pipe();
	if (ast)
		pid = fill_pipe(ast, pid);
	waitpid(ms()->last_pid, &status, 0);
	while (waitpid(0, NULL, 0) > 0)
		continue ;
	if (WIFEXITED(status))
		ms()->exit = WEXITSTATUS(status);
	signal_default();
}
