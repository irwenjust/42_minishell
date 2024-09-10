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
	t_ast	*red;

	//get redir operator
	red = ast_new(token_copy(token_manager(CUR)));
	if (!red)
		return (NULL);
	//move to next token, should be the direction of redir
	token_manager(NEXT);
	//add direction to redir's arg
	red->arg = matrix_add(red->arg, ft_strdup(token_manager(CUR)->tk));
	//insert redir to the left of cmd node
	red->left = cmd->left;
	cmd->left = red;
	return (cmd);
}

/*parse command func*/
static t_ast	*parse_cmd(void)
{
	t_ast	*cmd;

	//create ast with token, and initialize arg memory
	cmd = ast_new(token_copy(token_manager(CUR)));
	if (!cmd)
		return (NULL);
	//why need this????????????????????????
	cmd->index = ms()->cmd_nb++;
	//loop until end of token or meet pipe
	while (token_manager(CUR) && token_manager(CUR)->type != TK_PIPE)
	{
		// if current token is redir, need to parse redir
		if (token_manager(CUR)->type >= TK_IN_RE
			&& token_manager(CUR)->type <= TK_APPEND)
			cmd = redirection_cmd(cmd);
		//get the arg of cmd mode
		else
			cmd->arg = matrix_add(cmd->arg, ft_strdup(token_manager(CUR)->tk));
		//move to next token
		token_manager(NEXT);
	}
	return (cmd);
}

/*patrse func to creat ast*/
void	parser(void)
{
	t_ast	*cmd;

	token_manager(RESET);
	cmd = NULL;
	//get first cmd, token will be move to next one inside parse_cmd func
	(ms()->ast) = parse_cmd();
	if (!(ms()->ast))
		return ;
	//so if only one pipe, token(CUR) is NULL now, and would not go into this while loop
	//if there is more than one pipes, go into loop to parse each one by one
	while (token_manager(CUR) && token_manager(CUR)->type == TK_PIPE)
	{
		//CUR token is '|', need to be move to next token
		token_manager(NEXT);
		cmd = parse_cmd();
		//after parsing cmd, manage pipe, why after?????????
		(ms()->ast) = parse_pipe(ms()->ast, cmd);
	}
}
