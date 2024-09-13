#include "minishell.h"

bool	check_quote(void)
{
	int		i;
	char	quote;
	bool	start_quote;

	i = 0;
	quote = '\"';
	start_quote = false;
	while (ms()->input[i])
	{
		if (!start_quote && ft_strchr("\"\'", ms()->input[i]))
		{
			quote = ms()->input[i];
			start_quote = true;
		}
		else if (start_quote && ms()->input[i] == quote)
			start_quote = false;
		i++;
	}
	if (start_quote)
	{
		show_error("unclosed quotes", -1, 1);
		return (false);
	}
	return (true);
}

bool	check_syntax(void)
{
	t_token	*next;
	int		pipe_nb;
	int		cmd_nb;

	pipe_nb = 0;
	cmd_nb = 1;
	token_manager(RESET);
	if (is_pipe(token_manager(CUR)))
		return (show_error("syntax error near unexpected token `|'", -1, 1));
	while (token_manager(CUR))
	{
		next = token_manager(PREVIEW);
		if (is_redir(token_manager(CUR)) && (!next || is_redir_or_pipe(next)))
			return (syntax_error(next));
		if (token_manager(CUR)->type == TK_PIPE)
		{
			pipe_nb++;
			if (next && !is_pipe(next))
				cmd_nb++;
		}
		token_manager(NEXT);
	}
	if (pipe_nb >= cmd_nb)
		return (show_error("syntax error near unexpected token `|'", -1, 1));
	return (true);
}