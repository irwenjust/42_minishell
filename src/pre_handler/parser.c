/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:23:23 by likong            #+#    #+#             */
/*   Updated: 2024/09/05 13:33:57 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pipe manager
static t_ast	*parse_pipe(t_ast *ast, t_ast *cmd)
{
	t_ast	*res;

	if (!ast || !cmd)
		return (NULL);
	//add pipe into ast, token is pipe, arg is NULL
	res = ast_new(token_new(ft_strdup("|"), TK_PIPE, false));
	if (!res)
		return (NULL);
	//insert all previous ast to pipe left
	ast_insert(&res, ast, true);
	//insert next cmd to pipe right
	ast_insert(&res, cmd, false);
	return (res);
}

//redir parse
static t_ast	*redirection_cmd(t_ast *cmd)
{
	t_ast	*res;

	//get redir operator
	res = ast_new(token_copy(token_manager(CUR)));
	if (!res || !cmd)
		return (NULL);
	//move to next token, should be the direction of redir
	token_manager(NEXT);
	//add direction to redir's arg
	res->arg = matrix_add(res->arg, ft_strdup(token_manager(CUR)->tk));
	//insert redir to the left of cmd node
	res->left = cmd->left;
	cmd->left = res;
	return (cmd);
}

/*parse command func*/
static t_ast	*parse_cmd(void)
{
	t_ast	*cmd;

	cmd = ast_new(token_copy(token_manager(CUR)));
	if (!cmd)
		return (NULL);
	cmd->index = ms()->cmd_nb++;
	//loop until end of token or meet pipe
	while (token_manager(CUR) && token_manager(CUR)->type != TK_PIPE)
	{
		// if current token is redir, need to parse redir
		if (token_manager(CUR)->type >= TK_IN_RE
			&& token_manager(CUR)->type <= TK_APPEND)
		{
			cmd = redirection_cmd(cmd);
			if (!cmd)
				return (NULL);
		}
		else
			cmd->arg = matrix_add(cmd->arg, ft_strdup(token_manager(CUR)->tk));
		token_manager(NEXT);
	}
	return (cmd);
}

t_ast *change_fist_token(t_ast *cmd, int need_change)
{
	if (!cmd)
		return (NULL);
	if (need_change == 1)
	{
		ft_free(cmd->token->tk);
		cmd->token->tk = ft_strdup(cmd->arg[0]);
		cmd->token->type = TK_KEYWORD;
	}
	return (cmd);
}

/*patrse func to creat ast*/
bool	parser(void)
{
	t_ast	*cmd;
	int need_chage;

	cmd = NULL;
	need_chage = 0;
	token_manager(RESET);
	if (token_manager(CUR)->type >= TK_IN_RE && token_manager(CUR)->type <= TK_APPEND)
		need_chage = 1;
	(ms()->ast) = parse_cmd();
	if (!(ms()->ast))
		return (false);
	(ms()->ast) = change_fist_token((ms()->ast), need_chage);
	while (token_manager(CUR) && token_manager(CUR)->type == TK_PIPE)
	{
		need_chage = 0;
		token_manager(NEXT);
		if (token_manager(CUR)->type >= TK_IN_RE && token_manager(CUR)->type <= TK_APPEND)
			need_chage = 1;
		cmd = parse_cmd();
		cmd = change_fist_token(cmd, need_chage);
		(ms()->ast) = parse_pipe(ms()->ast, cmd);
		if (!(ms()->ast))
			return (false);
	}
	return (true);
}
