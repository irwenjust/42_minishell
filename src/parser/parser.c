/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:23:23 by likong            #+#    #+#             */
/*   Updated: 2024/08/29 14:27:39 by likong           ###   ########.fr       */
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
	if (!ft_strcmp(cmds[0], "pwd") && matrix_size(cmds) == 1)
		printf("%s\n", ms()->cwd);
	delete_matrix(cmds);
}
