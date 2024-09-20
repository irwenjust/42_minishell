/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:32:23 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/20 08:28:29 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_heredoc(int signal)
{
	if (signal != SIGINT)
		return ;
	printf("\n");
	restart(true);
	(ms()->exit) = 130;
}
