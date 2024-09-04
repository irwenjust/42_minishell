/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:37:11 by likong            #+#    #+#             */
/*   Updated: 2024/08/29 14:27:31 by likong           ###   ########.fr       */
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
    //     printf("%s\n", ((t_token *)(cur->content))->input);
    //     cur = cur->next;
    // }
	
//parse
	
	// expander();
	//parser();

    return ;
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
			clean_all(true);
		}
		add_history(ms()->input);
		//lexer and parse
		pre_handle();

		//exexution();
		start_parse();

		clean_all(false);
	}
	rl_clear_history();
}
