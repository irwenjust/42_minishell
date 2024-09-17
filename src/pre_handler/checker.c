/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:23:02 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/13 15:23:24 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_err("unclosed quotes", -1, 1);
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
		return (ft_err("syntax error near unexpected token `|'", -1, 1));
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
		return (ft_err("syntax error near unexpected token `|'", -1, 1));
	return (true);
}

t_list *check_empty(t_list *lexer_tk)
{
	t_list *head;
	t_list *tmp;
	t_list *pre;
	t_token *current;
	int i;

	i = 0;
	head = lexer_tk;
	while (lexer_tk)
	{
		current = lexer_tk->content;
		if (ft_strlen(current->tk) == 0)
		{
			tmp = lexer_tk;
			lexer_tk = lexer_tk->next;
			if (i == 0)
				head = lexer_tk;
			else
				pre->next = lexer_tk;
			ft_lstdelone(tmp, (void *)token_delete);
			tmp = NULL;
		}
		else
		{
			i = 1;
			pre = lexer_tk;
			lexer_tk = lexer_tk->next;
		}
	}
	return (head);
}
