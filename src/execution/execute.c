/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:44:05 by likong            #+#    #+#             */
/*   Updated: 2024/09/18 21:43:44 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_close(void)
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

// Might need change later
static int	exec_others(char **cmds)
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
		if (S_ISDIR(path_stat.st_mode))
			status = ft_err(cmds[0], DIRECTORY, FAIL_EXEC);
		else if (S_ISREG(path_stat.st_mode))
		{
			execve(path, cmds, ms()->envp);
			if (cmds[0][0] != '$')
				status = ft_err(cmds[0], PERMISSION, FAIL_EXEC);
		}
		ft_free(path);
	}
	else if (ft_strchr(cmds[0], '/'))
		status = ft_err(cmds[0], FILE_NAME, FAIL_FCMD);
	else if (ft_strlen(cmds[0]) >= 1)
		status = ft_err(cmds[0], COMMAND, FAIL_FCMD);
	return (status);
}

static int	handle_command(char **cmds)
{
	int	status;

	status = 0;
	if (!is_builtin(cmds[0]))
	{
		// printf("there\n");
		status = exec_others(cmds);
		// printf("here\n");
	}
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

static int	exec_re(t_ast *node)
{
	int	status;

	status = 0;
	if (!node)
		return (status);
	status = exec_re(node->left);
	// status = exec_re(node->right);
	if (ms()->in_fd == -1 || ms()->out_fd == -1)
		restart(true);
	//printf("token: %s, arg: %s\n", node->token->tk, node->arg[0]);
	if (is_redir(node->token) && node->arg[0])
	{
		// printf("here\n");

		redirect(node->token->type, node->arg[0]);
		// printf("Here?\n");

		apply_fd(node->index);
		
		dup_fd();
		// printf("come\n");

		//close_fd(node->index);
		//new_close();
		return (status);
	}
	apply_fd(node->index);
	dup_fd();
	//close_fd(node->index);
	// printf("arg: %s\n", node->arg[0]);
	new_close();
	// printf("in: %d, out: %d\n", ms()->in_fd, ms()->out_fd);
	status = handle_command(node->arg);
	// restart(true);
	//printf("status: %d\n", status);
	return (status);
}

//missed signal function
static pid_t	handle_child_process(t_ast *node)
{
	pid_t	pid;

	signal_child();
	pid = fork();
	if (pid < 0)
		ft_err(NULL, FORK, FAIL_STD);
	else if (pid == 0)
	{
	
		exec_re(node);
		// close_fd(node->index);
		restart(true);
	}
	close_fd(node->index);
	// new_close();
	return (pid);
}

static pid_t	fill_pipe(t_ast *node)
{
	pid_t		pid;

	pid = 0;
	if (!node)
		return (pid);
	while (node)
	{
		if (is_pipe(node->token))
		{
			pid = handle_child_process(node->right);
			if (!is_pipe(node->left->token))
			{
				if (!ft_strcmp(node->left->arg[0], "exit") && ms()->cmd_nb == 1)
					handle_command(node->left->arg);
				else if (node->left->token->type != TK_LOC_V)
					pid = handle_child_process(node->left);
				break ;
			}
		}
		else if (is_unfork(node->arg[0], node->arg[1]))
		{
			handle_command(node->arg);
			break ;
		}
		else if (!is_pipe(node->token) && node->token->type != TK_LOC_V)
		{
			pid = handle_child_process(node);
			break ;
			// handle_command(node->arg);
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
	create_pipe();
	pid = fill_pipe(ast);
	// close_fd(ast->index);
	// printf("pre status: %d\n", status);
	pid = waitpid(pid, &status, 0);
	// printf("status: %d\n", status);
	while (waitpid(0, NULL, 0) > 0)
		continue ;
	if (WIFEXITED(status))
		ms()->exit = WEXITSTATUS(status);
	signal_default();
}
