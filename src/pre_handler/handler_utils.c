#include "minishell.h"

bool is_redir_or_pipe(t_token *token)
{
	if (token->type >= TK_PIPE && token->type <= TK_APPEND)
		return (true);
	return (false);
}

bool is_redirection(t_token *token)
{
	if (token->type >= TK_IN_RE && token->type <= TK_APPEND)
		return (true);
	return (false);
}