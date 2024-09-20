/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:58:01 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/19 21:08:04 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_default(void)
{
	// printf("parent\n");
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_child(void)
{
	// struct sigaction	sa;

	// sigemptyset(&sa.sa_mask);
	// sa.sa_flags = 0;
	// sa.sa_handler = handle_child;
	// // printf("child\n");
	// sigaction(SIGINT, &sa, NULL);

    // // Register the handler for SIGQUIT
    // sigaction(SIGQUIT, &sa, NULL);
	// sigset_t newmask;
    // sigemptyset(&newmask);  // Initialize an empty signal set
    // sigaddset(&newmask, SIGINT);  // Add SIGINT to the set
    // sigaddset(&newmask, SIGQUIT); // Add SIGQUIT to the set
    // sigprocmask(SIG_UNBLOCK, &newmask, NULL);  // Unblock the signals
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	// restart(false);
}

void	signal_heredoc(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_ignore(void)
{
	// printf("ignore\n");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
