/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
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
