/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:37:11 by likong            #+#    #+#             */
/*   Updated: 2024/09/13 12:00:11 by likong           ###   ########.fr       */
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
void print_ast_arg(t_ast *node, int depth, int is_left) 
{
    if (node == NULL)
        return;

    // Print indentation
    for (int i = 0; i < depth; i++)
        printf("    ");
    
    // Print the node
    if (depth > 0) {
        if (is_left)
            printf("├── ");
        else
            printf("└── ");
    }
    printf("Index: %d, Token: %s", node->index, node->token ? node->token->tk : "NULL");
	int j = 0;
     if (node->token)
     {
		printf(", arg: ");
		if (node->arg[j] == NULL)
		{
			printf("%s", "null");
			j++;
		}
		while (node->arg && node->arg[j])
		{
			if (node->arg[j])
        		printf("%s, ", node->arg[j]);
        	j++;
		}
     }
	 printf("\n");
    // Recursively print the left and right subtrees
    print_ast_arg(node->left, depth + 1, 1);
    print_ast_arg(node->right, depth + 1, 0);
}

void print_ast_arg(t_ast *node) 
{

	t_ast *left_node = NULL;
	t_ast *right_node = NULL;
	t_ast *cur;
	int j;
	
	if (node == NULL)
        return;
	
	cur = node->left->right;
	while (cur)
	{
		
		printf("Index: %d, Token:%s", cur->index, cur->token ? cur->token->tk : "NULL");
		j = 0;
		if (cur->token)
     	{
			printf(", arg: ");
			if (cur->arg[j] == NULL)
			{
				printf("%s", "null");
				j++;
			}
			while (cur->arg && cur->arg[j])
			{
				if (cur->arg[j])
        			printf("%s, ", cur->arg[j]);
        		j++;
			}
     	}
		//if(cur->right)
		//	printf("right\n");
		//if(cur->left)
		//	printf("left\n");
		cur = cur->right;
	}

	left_node = node->left;
	printf("\n");
	printf("Index: %d, Token:%s", left_node->index, left_node->token ? left_node->token->tk : "NULL");
	printf("\n");
	right_node = left_node->right;
	printf("Index: %d, Token:%s", right_node->index, right_node->token ? right_node->token->tk : "NULL");
	printf("\n");
	printf("Index: %d, Token:%s", node->index, node->token ? node->token->tk : "NULL");
	
	printf("\n");
	right_node = node->right;
	printf("Index: %d, Token:%s", right_node->index, right_node->token ? right_node->token->tk : "NULL");
	printf("\n");
}

bool	pre_handle(void)
{
//lexer
    if (!check_quote())
        return (false);
    lexer();
	if (!check_syntax())
		return (false);
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
	// 	printf("expander: %s\n", ((t_token *)(exp->content))->tk);
    //     exp = exp->next;
    // }

//parser
	parser();
	//test parse
	 t_ast *ast = ms()->ast;
     print_ast_arg(ast, 0, 0);
	 //print_ast_arg(ast);

    return (true);
}
*/

// static int only_local(t_ast *ast)
// {
// 	static int	status = 1;
// 	if (!ast)
// 	{
// 		printf("stat: %d\n", status);
// 		return (status);
// 	}
// 	only_local(ast->left);
// 	only_local(ast->right);
// 	printf("%s\n", ast->token->tk);
// 	if (!is_local_variable(ast->token))
// 	{
// 		printf("Here\n");
// 		status = 0;
// 	}
// 	return (status);
// }

static int	check_all_local(void)
{
	t_list	*tmp;

	tmp = ms()->lexer_tk;
	while (tmp)
	{
		if (!is_local_variable(tmp->content))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static bool	pre_handle(void)
{
	if (!check_quote())
		return (false);
	if (!lexer())
		return (false);
	if (!check_syntax())
		return (false);
	 
	expander();
	//t_list *exp;
    // exp = ms()->lexer_tk;
    // while (exp)
    // {
	// 	printf("[%s]\n", ((t_token *)(exp->content))->tk);
	//	printf("[%u]\n", ((t_token *)(exp->content))->type);
    //     exp = exp->next;
    // }
	if (!parser())
		return (false);
	if (check_all_local())
		return (false);
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
		update_env();
		unlink("here_doc");
		restart(false);
	}
	rl_clear_history();
}
