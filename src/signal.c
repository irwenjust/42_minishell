/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:58:01 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/05 12:59:27 by yzhan            ###   ########.fr       */
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

void	singal_default(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
