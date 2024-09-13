/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:14:53 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/05 13:15:30 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir_or_pipe(t_token *token)
{
	if (!token)
		return (false);
	if (token->type >= TK_PIPE && token->type <= TK_APPEND)
		return (true);
	return (false);
}

bool	is_redir(t_token *token)
{
	if (!token)
		return (false);
	if (token->type >= TK_IN_RE && token->type <= TK_APPEND)
		return (true);
	return (false);
}

bool	is_pipe(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == TK_PIPE)
		return (true);
	return (false);
}

bool	is_local_variable(t_token *token)
{
	int	i;

	i = -1;
	if (token->tk[0] && token->tk[0] == '=')
	{
		show_error(token->tk, COMMAND, FAIL_FCMD);
		return (false);
	}
	while (token->tk[++i])
	{
		if (token->tk[i] == '=')
		{
			add_node_for_local(&ms()->local_var, token->tk);
			return (true);
		}
	}
	return (false);
}
