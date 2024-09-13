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
	//insert all previous ast to pipe left
		//insert next cmd to pipe right
static t_ast	*parse_pipe(t_ast *ast, t_ast *cmd)
{
	t_ast	*res;

	if (!ast || !cmd)
		return (NULL);
	res = ast_new(token_new(ft_strdup("|"), TK_PIPE, false));
	if (!res)
		return (NULL);
	ast_insert(&res, ast, true);
	ast_insert(&res, cmd, false);
	return (res);
}

//redir parse
	//add direction to redir's arg
	//insert redir to the left of cmd node
static t_ast	*redirection_cmd(t_ast *cmd)
{
	t_ast	*res;

	res = ast_new(token_copy(token_manager(CUR)));
	if (!res || !cmd)
		return (NULL);
	token_manager(NEXT);
	res->arg = matrix_add(res->arg, ft_strdup(token_manager(CUR)->tk));
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
	while (token_manager(CUR) && token_manager(CUR)->type != TK_PIPE)
	{
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

t_ast	*change_fist_token(t_ast *cmd, int need_change)
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
	int		need_chage;

	cmd = NULL;
	need_chage = 0;
	token_manager(RESET);
	if (is_redir(token_manager(CUR)) && token_manager(CUR)->type != TK_HDOC)
		need_chage = 1;
	(ms()->ast) = parse_cmd();
	if (!(ms()->ast))
		return (false);
	(ms()->ast) = change_fist_token((ms()->ast), need_chage);
	while (token_manager(CUR) && token_manager(CUR)->type == TK_PIPE)
	{
		need_chage = 0;
		token_manager(NEXT);
		if (is_redir(token_manager(CUR)) && token_manager(CUR)->type != TK_HDOC)
			need_chage = 1;
		cmd = parse_cmd();
		cmd = change_fist_token(cmd, need_chage);
		(ms()->ast) = parse_pipe(ms()->ast, cmd);
		if (!(ms()->ast))
			return (false);
	}
	return (true);
}
