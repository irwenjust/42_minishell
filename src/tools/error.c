/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:20:14 by likong            #+#    #+#             */
/*   Updated: 2024/09/19 17:47:30 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_message(char *message, t_error err_type)
{
	if (message)
		ft_putstr_fd(message, STD_ERR);
	if (err_type == FORK)
		ft_putstr_fd("fork() error", STD_ERR);
	else if (err_type == MALLOC)
		ft_putstr_fd(": malloc() failed", STD_ERR);
	else if (err_type == PIPE)
		ft_putstr_fd("pipe() creation failed", STD_ERR);
	else if (err_type == PERMISSION)
		ft_putstr_fd(": Permission denied", STD_ERR);
	else if (err_type == FILE_NAME)
		ft_putstr_fd(": No such file or directory", STD_ERR);
	else if (err_type == DUP2)
		ft_putstr_fd("dup2() error", STD_ERR);
	else if (err_type == DIRECTORY)
		ft_putstr_fd(": Is a directory", STD_ERR);
	else if (err_type == COMMAND)
		ft_putstr_fd(": command not found", STD_ERR);
	else if (err_type == HERE_DOC)
		ft_putstr_fd("Could not open here_doc file", STD_ERR);
	ft_putchar_fd('\n', STD_ERR);
}

int	ft_err(char *message, t_error err_type, int err_fd)
{
	if (!find_env(ms()->env_list, "PATH") || err_type == FILE_NAME)
		ft_putstr_fd("minishell: ", STD_ERR);
	show_message(message, err_type);
	ms()->exit = err_fd;
	return (0);
}

int	syntax_error(t_token *next)
{
	if (!next)
		return (ft_err("syntax error near unexpected token `newline'", -1, 1));
	else if (next->type == TK_PIPE)
		return (ft_err("syntax error near unexpected token `|'", -1, 1));
	else if (next->type == TK_IN_RE)
		return (ft_err("syntax error near unexpected token `<'", -1, 1));
	else if (next->type == TK_OUT_RE)
		return (ft_err("syntax error near unexpected token `>'", -1, 1));
	else if (next->type == TK_HDOC)
		return (ft_err("syntax error near unexpected token `<<'", -1, 1));
	else if (next->type == TK_APPEND)
		return (ft_err("syntax error near unexpected token `>>'", -1, 1));
	return (0);
}
