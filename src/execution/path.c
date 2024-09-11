/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:29:50 by likong            #+#    #+#             */
/*   Updated: 2024/09/11 11:03:23 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Didn't handle error message still. May need change return value
static char	*absolute_path(char *exe)
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

	if (exe[0] == '.')
		path = relative_path(exe);
	else
		path = absolute_path(exe);
	return (path);
}
