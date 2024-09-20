/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:37:11 by likong            #+#    #+#             */
/*   Updated: 2024/09/20 09:19:00 by likong           ###   ########.fr       */
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
		ms()->lines++;
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
