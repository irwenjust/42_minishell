/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:59:03 by likong            #+#    #+#             */
/*   Updated: 2024/09/09 15:13:54 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			|| !ft_strcmp(cmd, "unset"));
}
