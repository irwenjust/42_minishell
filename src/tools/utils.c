/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:20:14 by likong            #+#    #+#             */
/*   Updated: 2024/09/11 12:08:55 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_message(char *message, t_error error)
{
	ft_putstr_fd("minishell: ", STD_ERR);
	if (message)
		ft_putstr_fd(message, STD_ERR);
	if (error == FORK)
		ft_putstr_fd("fork() error", STD_ERR);
	else if (error == MALLOC)
		ft_putstr_fd(": malloc() failed", STD_ERR);
	else if (error == PIPE)
		ft_putstr_fd("pipe() creation failed", STD_ERR);
	else if (error == PERMISSION)
		ft_putstr_fd(": Permission denied", STD_ERR);
	else if (error == FILE_NAME)
		ft_putstr_fd(": No such file or directory", STD_ERR);
	else if (error == DUP2)
		ft_putstr_fd("dup2() error", STD_ERR);
	else if (error == DIRECTORY)
		ft_putstr_fd(": Is a directory", STD_ERR);
	else if (error == COMMAND)
		ft_putstr_fd(": command not found", STD_ERR);
	else if (error == HERE_DOC)
		ft_putstr_fd("Could not open here_doc file", STD_ERR);
	else if (error == NEXT_LINE)
		ft_putstr_fd("warning: here_doc at line 50 delimited by \
		end-of-file", STD_ERR);
	ft_putchar_fd('\n', STD_ERR);
}

int	str_len(char *str, char *sep)
{
	int	i;

	i = 0;
	while (str[i] && !ft_strchr(sep, str[i]))
		i++;
	return (i);
}

int	error_info(char *info)
{
	if (info)
		ft_putstr_fd(info, 2);
	return (0);
}

void	show_error(char *message, t_error error, int err_fd)
{
	show_message(message, error);
	ms()->exit = err_fd;
	restart(true);
}
