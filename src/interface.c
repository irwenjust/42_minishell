/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:37:11 by likong            #+#    #+#             */
/*   Updated: 2024/09/11 15:37:49 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_prompt(void)
{
	char	*res1;
	char	*res2;

	res1 = ft_strjoin("minishell:", ms()->cwd);
	if (!res1)
		return (NULL);
	res2 = ft_strjoin(res1, "$ ");
	if (!res2)
	{
		ft_free(res1);
		return (NULL);
	}
	ft_free(res1);
	return (res2);
}
/*
 void print_ast_arg(t_ast *node)
 {
	static int i = 0;
     if (node == NULL)
         return ;
     int j = 0;
     if (node->token)
     {
		// printf("%i token: %s\n", i++, node->token->tk);
		if (node->arg[j] == NULL)
			printf("%i arg: %s\n", j++, "null");
		while (node->arg && node->arg[j])
		{
			if (node->arg[j])
        		printf("%i arg: %s\n", j, node->arg[j]);
        	j++;
		}
     }
	 
     print_ast_arg(node->left);
     print_ast_arg(node->right);
 }

void	pre_handle(void)
{
//lexer
    if (!check_quote())
        return ;
    lexer();
	if (!check_syntax())
		return ;
	//lexer test
    // t_list *cur;
    // cur = ms()->lexer_tk;
    // while (cur)
    // {
    //     printf("input: %s\n", ((t_token *)(cur->content))->tk);
	// 	printf("can merge: %i\n", ((t_token *)(cur->content))->mergeable);
    //     cur = cur->next;
    // }
	
//expander
	expander();
	//test expander
	// t_list *exp;
    // exp = ms()->lexer_tk;
    // while (exp)
    // {
	// 	printf("expander: %s\n", ((t_token *)(exp->content))->input);
    //     exp = exp->next;
    // }

//parser
	parser();
	//test parse
	 t_ast *ast = ms()->ast;
     print_ast_arg(ast);

    return ;
}
*/

static bool	pre_handle(void)
{
	if (!check_quote())
		return (false);
	lexer();
	if (!check_syntax())
		return (false);
	expander();
	parser();
	// print_ast_arg(ms()->ast);
	return (true);
}

void	start_shell(void)
{
	while (1)
	{
		ms()->prompt = set_prompt();
		ms()->input = readline(ms()->prompt);
		if (!ms()->input)
		{
			write(1, "exit\n", 5);
			restart(true);
		}
		add_history(ms()->input);
		if (pre_handle() == true)
			execute(ms()->ast);
		unlink("here_doc");
		restart(false);
	}
	rl_clear_history();
}
