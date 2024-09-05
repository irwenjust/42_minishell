/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:48:13 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/05 13:51:51 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *input, t_token_type type, bool mergeable)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->tk = input;
	token->type = type;
	token->mergeable = mergeable;
	return (token);
}

int	token_add(char *input, t_token_type type, bool mergeable)
{
	t_token	*token;

	token = token_new(input, type, mergeable);
	if (!token || !input)
		return (0);
	ft_lstadd_back(&ms()->lexer_tk, ft_lstnew(token));
	return (ft_strlen(input));
}

t_token	*token_copy(t_token *token)
{
	t_token	*copy;

	if (!token)
		return (NULL);
	copy = token_new(ft_strdup(token->tk), token->type, token->mergeable);
	if (!copy)
		return (NULL);
	return (copy);
}

void	token_delete(t_token *token)
{
	if (!token)
		return ;
	ft_free(token->tk);
	ft_free(token);
}

t_token	*token_manager(t_manager mg)
{
	static t_list	*current = NULL;

	if (mg == RESET)
		current = ms()->lexer_tk;
	else if (mg == CUR && current)
		return (current->content);
	else if (mg == NEXT)
		current = current->next;
	else if (mg == PREVIEW && current->next)
		return (current->next->content);
	return (NULL);
}
