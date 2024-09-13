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

/*
[cat "infi"le] [ca"t" infile] will be merged
merge "" with something out "" but without space or other symbols
merge char within "" but without space or other symbols
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
	if (!ft_strcmp(symbols, need_match) && ft_strchr(quote, input[end]))
		return (true);
	if (ft_strchr(quote, need_match[0]) && !ft_strchr(special, input[end + 1]))
		return (true);
	return (false);
}

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

static int lexer_redir(int i)
{
	int j;

	j = 0;
	if (!ft_strncmp(&(ms()->input[i]), "<<", 2))
		j = token_add(ft_strdup("<<"), TK_HEREDOC, false);
	else if (!ft_strncmp(&(ms()->input[i]), ">>", 2))
		j = token_add(ft_strdup(">>"), TK_APPEND, false);
	else if (ms()->input[i] == '<')
		j = token_add(ft_strdup("<"), TK_IN_RE, false);
	else if (ms()->input[i] == '>')
		j = token_add(ft_strdup(">"), TK_OUT_RE, false);
	return (j);
}

static int lexer_match(int i)
{
	int j;

	j = 0;
	if (ms()->input[i] == '"')
		j = find_match("\"", &ms()->input[i + 1]) + 2;
	else if (ms()->input[i] == '\'')
		j = find_match("\'", &ms()->input[i + 1]) + 2;
	else
		j = find_match("<>\'\"| ", &ms()->input[i]);
	return (j);
}

bool	lexer(void)
{
	int	i;
	int j;

	i = 0;
	while (ms()->input[i])
	{
		j = 0;
		if (ms()->input[i] == ' ')
			j++;
		else if (ms()->input[i] == '|')
			j = token_add(ft_strdup("|"), TK_PIPE, false);
		else if (ms()->input[i] == '<' || ms()->input[i] == '>')
			j = lexer_redir(i);
		else
			j = lexer_match(i);
		if (j == -1)
			return (false);
		i += j;
	}
	return (true);
}

