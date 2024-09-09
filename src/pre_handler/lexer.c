/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:15:51 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/05 13:29:38 by yzhan            ###   ########.fr       */
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
		error_info("minishell: unclosed quotes.\n");
		return (false);
	}
	return (true);
}

//还没有写道merge token的地方，所以不太理解这个merge的原理，可能回头写到那里能懂啥意思
/*
根据gpt, echo "hello" "world"3个token应该被合并成 echo "hello world"2个
但并没有，而是 echo "hello""world"可以被合并为2个token，即token中间没有space的情况下可以。
这似乎不太全面???还不太清楚哪些需要合并
如果去掉symbols和special里的space之后，就可以合并echo "hello" "world"了
看有的代码，并没有merge check这一项，盲猜可能不用这一条，在parse AST的时候再处理亦可。
*/
static bool	check_mergeable(char *need_match, char *input, int end)
{
	char	*symbols;
	char	*quote;
	char	*special;

	symbols = "<>\'\"| ";
	quote = "\'\"";
	special = "<>| ";
	if (!input[end])
		return (false);
    //if need match is special symbol, the end is quote, for quote match quote is ok, for <>|space, why find the quote end???
	if (!ft_strcmp(symbols, need_match) && ft_strchr(quote, input[end]))
		return (true);
	//when start match is quote, the end+1 is not <>|space, why????????
	if (ft_strchr(quote, need_match[0]) && !ft_strchr(special, input[end + 1]))
		return (true);
	return (false);
}

//find the end when meet quote or ?normal string?
static int	find_match(char *need_match, char *input)
{
	int		end;
	char	*tk_input;
	bool	mergeable;

	end = 0;
	while (input[end] && !ft_strchr(need_match, input[end]))
		end++;
	mergeable = check_mergeable(need_match, input, end);
	tk_input = ft_substr(input, 0, end);
	if (need_match[0] == '"')
		token_add(tk_input, TK_DOUBLE_QT, mergeable);
	else if (need_match[0] == '\'')
		token_add(tk_input, TK_SINGLE_QT, mergeable);
	else
		token_add(tk_input, TK_KEYWORD, mergeable);
	return (end);
}

//lexer function
void	lexer(void)
{
	int	i;

	i = 0;
	while (ms()->input[i])
	{
		if (ms()->input[i] == ' ')
			i++;
		else if (ms()->input[i] == '|')
			i += token_add(ft_strdup("|"), TK_PIPE, false); //????must use ft_strdup? can just "|" ">>"?
		else if (!ft_strncmp(&(ms()->input[i]), "<<", 2))
			i += token_add(ft_strdup("<<"), TK_HEREDOC, false);
		else if (!ft_strncmp(&(ms()->input[i]), ">>", 2))
			i += token_add(ft_strdup(">>"), TK_APPEND, false);
		else if (ms()->input[i] == '<')
			i += token_add(ft_strdup("<"), TK_IN_RE, false);
		else if (ms()->input[i] == '>')
			i += token_add(ft_strdup(">"), TK_OUT_RE, false);
		else if (ms()->input[i] == '"')
			i += find_match("\"", &ms()->input[i + 1]) + 2;
		else if (ms()->input[i] == '\'')
			i += find_match("\'", &ms()->input[i + 1]) + 2;
		else
			i += find_match("<>\'\"| ", &ms()->input[i]); //to find the end of a cmd?
	}
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
		return (error_info("Wrong syntax: first token cannot be a pipe.\n"));
	while (token_manager(CUR))
	{
		next = token_manager(PREVIEW);
		if (is_redir(token_manager(CUR)) && (!next || is_redir_or_pipe(next)))
			return (error_info("Wrong syntax: no dir after redirection.\n"));
		if (token_manager(CUR)->type == TK_PIPE)
		{
			pipe_nb++;
			if (next && !is_redir_or_pipe(next))
				cmd_nb++;
		}
		token_manager(NEXT);
	}
	if (pipe_nb >= cmd_nb)
		return (error_info("Wrong syntax: too much pipes without cmds.\n"));
	return (true);
}
