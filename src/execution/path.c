/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:29:50 by likong            #+#    #+#             */
/*   Updated: 2024/09/19 12:22:17 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_error(struct stat stat, char *path, int status, char **cmds)
{
	if (S_ISDIR(stat.st_mode))
		status = ft_err(cmds[0], DIRECTORY, FAIL_EXEC);
	else if (S_ISREG(stat.st_mode))
	{
		execve(path, cmds, ms()->envp);
		if (cmds[0][0] != '$')
			status = ft_err(cmds[0], PERMISSION, FAIL_EXEC);
	}
	return (status);
}

static char	*absolute_path(char *exe)
{
	char	*tmp;
	char	*path;
	int		i;

	i = -1;
	if (exe[0] == '\0')
		return (NULL);
	if (access(exe, F_OK) == 0 && access(exe, X_OK) == 0 && ft_strchr(exe, '/'))
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

static char	*relative_path(char *exe)
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

char	*get_path(char *exe)
{
	char	*path;

	path = NULL;
	if (!exe)
		return (NULL);
	if (exe[0] == '.')
		path = relative_path(exe);
	else
		path = absolute_path(exe);
	return (path);
}
