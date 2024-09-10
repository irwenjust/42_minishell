/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:44:05 by likong            #+#    #+#             */
/*   Updated: 2024/09/10 09:26:35 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_absolute_path(char *exe)
{
	char	*tmp;
	char	*path;
	int		i;

	i = -1;
	if (exe[0] == '\0')
		return (NULL);
	if (access(exe, F_OK) == 0)
	{
		path = ft_strjoin("", exe);
		return (path);
	}
	while (ms()->path[++i])
	{
		tmp = ft_strjoin(ms()->path[i], "/");
		path = ft_strjoin(tmp, exe);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

char	*get_relative_path(char *exe)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(ms()->cwd, "/");
	path = ft_strjoin(tmp, exe + 2);
	free(tmp);
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	if (access(exe, F_OK) == 0)
		return (ft_strdup(exe));
	return (NULL);
}

char	*get_executable_path(char *exe)
{
	char	*path;

	if (exe[0] == '.')
		path = get_relative_path(exe);
	else
		path = get_absolute_path(exe);
	return (path);
}

static void	exec_others(char **cmds)
{
	char		*path;
	struct stat	path_stat;

	path = get_executable_path(cmds[0]);
	stat(path, &path_stat);
	if (path)
	{
		if (S_ISDIR(path_stat.st_mode))
			ft_putstr_fd("error 1", 2);
		else if (S_ISREG(path_stat.st_mode))
		{
			execve(path, cmds, ms()->envp);
			ft_putstr_fd("error 2", 2);
		}
		ft_free(path);
	}
	else
		ft_putstr_fd("error 3", 2);
	return ;
}

static void	handle_command(char **cmds)
{
	if (!is_builtin(cmds[0]))
		exec_others(cmds);
	if (!ft_strcmp(cmds[0], "exit") && ms()->cmd_nb == 1)
		ft_exit(cmds);
	else if (!ft_strcmp(cmds[0], "pwd") && matrix_size(cmds) == 1)
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp(cmds[0], "env") && matrix_size(cmds) == 1)
		print_env();
}

//missed signal function
static pid_t	handle_child(t_ast *node)
{
	pid_t	pid;

	pid = fork();
	(void)node;
	if (pid < 0)
	{
		ft_putstr_fd("Some mistake happend when fork process.\n", 2);
		restart(true);
	}
	else if (pid == 0)
	{
		//didn't check in_fd and out_fd here
		if (ms()->cmd_nb < 2)
			return (0);
		if (ms()->in_fd == STD_IN)
			if (node->index != 0)
				ms()->in_fd = ms()->fds[node->index - 1][READ];
		if (ms()->out_fd == STD_OUT)
			// Doubts about cmd_nb and index
			if (node->index < ms()->cmd_nb - 1)
				ms()->out_fd = ms()->fds[node->index][WRITE];
		// dup_fd();
		handle_command(node->arg);
		restart(true);
	}
	// close_fd(node->index);
	return (pid);
}

static pid_t	fill_pipe(t_ast *node)
{
	pid_t	pid;

	pid = 0;
	if (!node)
		return (pid);
	pid = fill_pipe(node->left);
	pid = fill_pipe(node->right);
	if (!is_redir(node->token))
	{
		if (is_unfork(node->arg[0], node->arg[1]))
			handle_command(node->arg);
		else
			pid = handle_child(node);
	}
	// else if (is_redir(node->token))
	// 	redirect(node->token->type, node->arg[0]);
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
	pid = waitpid(pid, &status, 0);
	while (waitpid(0, NULL, 0) > 0)
		continue ;
	if (WIFEXITED(status))
		ms()->exit = WEXITSTATUS(status);
	singal_default();
}
