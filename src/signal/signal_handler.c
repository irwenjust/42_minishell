/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:32:23 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/19 17:09:40 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
rl_replace_line(const char *text, int clear_undo);
	text is used to replace current line,
	clear_undo is 0 means not to clear the list. 
	this func is use to clear current command line.
rl_on_new_line(void);
	tell readline lib now is on a new line,
	and func will restart for new command.
rl_redisplay(void);
	display the readline buffer on screen.
*/
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

void	handle_child(int signal)
{
	if (signal == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (signal == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	(ms()->exit) = 128 + signal;
}

void	handle_heredoc(int signal)
{
	if (signal != SIGINT)
		return ;
	printf("\n");
	restart(true);
	(ms()->exit) = 130;
}
