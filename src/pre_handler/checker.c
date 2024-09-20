/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:23:02 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/20 09:38:01 by yzhan            ###   ########.fr       */
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
		ft_err("unclosed quotes", STX, 1);
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
		return (ft_err("syntax error near unexpected token `|'", STX, 1));
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
		return (ft_err("syntax error near unexpected token `|'", STX, 1));
	return (true);
}

static t_list	*delete_empty_node(t_list *lexer_tk)
{
	t_list	*tmp;

	tmp = lexer_tk;
	lexer_tk = lexer_tk->next;
	ft_lstdelone(tmp, (void *)token_delete);
	tmp = NULL;
	return (lexer_tk);
}

t_list	*check_empty(t_list *lexer_tk)
{
	t_list	*head;
	t_list	*pre;
	t_token	*current;

	pre = NULL;
	head = lexer_tk;
	while (lexer_tk)
	{
		current = lexer_tk->content;
		if (ft_strlen(current->tk) == 0)
		{
			if (!pre)
				head = lexer_tk->next;
			else
				pre->next = lexer_tk->next;
			lexer_tk = delete_empty_node(lexer_tk);
		}
		else
		{
			pre = lexer_tk;
			lexer_tk = lexer_tk->next;
		}
	}
	return (head);
}
