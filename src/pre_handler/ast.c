/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:00:36 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/05 13:01:54 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast_new(t_token *token)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->token = token;
	node->arg = ft_calloc(1, sizeof(char *));
	return (node);
}

void	ast_insert(t_ast **ast, t_ast *node, bool left)
{
	if (*ast && left)
		(*ast)->left = node;
	else if (*ast && !left)
		(*ast)->right = node;
	else
		*ast = node;
}

void	ast_delone(t_ast *ast)
{
	token_delete(ast->token);
	matrix_delete(ast->arg);
}

void	ast_clear(t_ast *ast, void (*del)(t_ast *))
{
	if (!ast)
		return ;
	ast_clear(ast->left, del);
	ast_clear(ast->right, del);
	del(ast);
	ft_free(ast);
}
