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

bool check_syntax(void)
{
	t_token *next;
	int pipe_nb;
	int cmd_nb;

	token_manager(RESET); //TODO
	//if first token is TK_PIPE <= token <= TK_APPEND (pipe or redir), error
	if (is_redir_or_pipe(token_manager(CURRENT)))
	{
		printf("Wrong syntax: first token is redirection or pipe.\n");
		return (0);
	}
	while (token_manager(CURRENT))
	{
		next = token_manager(PREVIEW);
		if (is_redirection(token_manager(CURRENT)) && (!next || is_redir_or_pipe(next)))
		{
			printf("Wrong syntax: no dir after redirection.\n");
			return (0);
		}
		if (token_manager(CURRENT)->type == TK_PIPE)
	}
}
