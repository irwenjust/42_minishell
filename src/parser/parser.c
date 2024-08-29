/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:23:23 by likong            #+#    #+#             */
/*   Updated: 2024/08/29 18:02:50 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_parse(void)
{
	char	**cmds;

	cmds = split_plus(ms()->input, ' ');
	if (!cmds)
		return ;
	if (!ft_strcmp(cmds[0], "exit"))
		ft_exit(cmds);
	else if (!ft_strcmp(cmds[0], "pwd") && matrix_size(cmds) == 1)
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp(cmds[0], "env") && matrix_size(cmds) == 1)
		print_env();
	delete_matrix(cmds);
}
