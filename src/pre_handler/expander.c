/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:02:10 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/05 13:14:09 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_keyword(char *str, char *old, char *new)
{
	int		len;
	char	*res;
	char	*find_old;
	char	*tmp;

	if (!str || !old || !new)
		return (NULL);
	len = ft_strlen(str) + ft_strlen(new) - ft_strlen(old);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	find_old = ft_strnstr(str, old, ft_strlen(str));
	if (!find_old)
		return (NULL);
	tmp = ft_substr(str, 0, (find_old - str));
	ft_strlcat(res, tmp, len + 1);
	ft_strlcat(res, new, len + 1);
	ft_strlcat(res, (find_old + ft_strlen(old)), len + 1);
	ft_free(tmp);
	return (res);
}

char	*find_keyword(char *str)
{
	char	*tmp;
	char	*keyword;
	int		i;

	tmp = ft_strnstr(str, "$", ft_strlen(str));
	if (!tmp || tmp[1] == ' ')
		return (NULL);
	if (tmp[1] == '?')
	{
		keyword = ft_strdup("$?");
		return (keyword);
	}
	i = 1;
	while (ft_isalnum(tmp[i]) || tmp[i] == '_')
		i++;
	keyword = ft_substr(tmp, 0, i);
	return (keyword);
}

static void	expand_current(t_token *token)
{
	char	*keyword;
	char	*real_key;
	char	*tmp;

	if (token->tk[0] == '$' && (ft_strlen(token->tk) == 1 || (ft_strlen(token->tk) > 1 && token->tk[1] == ' ')))
		return ;
	while (ft_strnstr(token->tk, "$", ft_strlen(token->tk)))
	{
		keyword = find_keyword(token->tk);
		if (!keyword)
			return ;
		if (!ft_strcmp(keyword, "$?"))
			real_key = ft_itoa(ms()->exit);
		else
			real_key = get_env(keyword);
		tmp = token->tk;
		token->tk = replace_keyword(token->tk, keyword, real_key);
		ft_free(keyword);
		ft_free(real_key);
		ft_free(tmp);
	}
}

static void	merge(t_list *lexer_tk)
{
	t_token	*current;
	t_token	*next;
	char	*tmp;
	t_list	*delete;

	while (lexer_tk)
	{
		current = lexer_tk->content;
		if (!lexer_tk->next)
			return ;
		if (!current->mergeable)
		{
			lexer_tk = lexer_tk->next;
			continue ;
		}
		next = lexer_tk->next->content;
		tmp = current->tk;
		current->tk = ft_strjoin(current->tk, next->tk);
		free(tmp);
		if (!next->mergeable)
			current->mergeable = next->mergeable;
		delete = lexer_tk->next;
		lexer_tk->next = lexer_tk->next->next;
		ft_lstdelone(delete, (void *)token_delete);
	}
}

void	expander(void)
{
	t_token	*current;

	token_manager(RESET);
	while (token_manager(CUR))
	{
		current = token_manager(CUR);
		//if (current->type == TK_HDOC)
		//	token_manager(NEXT);
		if (current->type == TK_DOUBLE_QT || current->type == TK_KEYWORD)
			expand_current(current);
		if (is_local_variable(current))
			current->type = TK_LOC_V;
		token_manager(NEXT);
	}
	merge(ms()->lexer_tk);
}
