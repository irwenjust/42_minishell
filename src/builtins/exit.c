/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:45:27 by likong            #+#    #+#             */
/*   Updated: 2024/08/30 10:44:45 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_status(char *str)
{
	int	sig;
	
	sig = 0;
	if (!ft_isnum(str))
		return (1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sig = 1;
		str++;
	}
	if (ft_strlen(str) > 19)
		return (1);
	if (sig)
		return (ft_strcmp(str, "9223372036854775808") > 0);
	else
		return (ft_strcmp(str, "9223372036854775807") > 0);
}

void	ft_exit(char **strs)
{
	if (matrix_size(strs) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ms()->exit = 1;
		return ;
	}
	if (matrix_size(strs) == 2 && check_status(strs[1]))
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(strs[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ms()->exit = 2;
	}
	else if (matrix_size(strs) == 2)
	{
		ft_putstr_fd("exit\n", 1);
		ms()->exit = ft_atoi(strs[1]) % 256;
	}
	delete_matrix(strs);
	clean_all(true);
}
