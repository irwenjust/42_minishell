/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:23:09 by likong            #+#    #+#             */
/*   Updated: 2024/09/11 15:25:31 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *p)
{
	if (p)
		free(p);
	p = NULL;
}

void	delete_env(t_env *env)
{
	ft_free(env->key);
	ft_free(env->value);
	ft_free(env);
}

void	restart(bool status)
{
	ft_free(ms()->prompt);
	ft_free(ms()->input);
	matrix_delete(ms()->fds);
	ast_clear(ms()->ast, ast_delone);
	ft_lstclear(&ms()->lexer_tk, (void (*)(void *))token_delete);

	(ms()->fds) = NULL;
	(ms()->ast) = NULL;
	(ms()->lexer_tk) = NULL;
	(ms()->cmd_nb) = 0;
	if (status)
	{
		ft_free(ms()->cwd);
		matrix_delete(ms()->path);
		matrix_delete(ms()->envp);
		ft_lstclear(&ms()->env_list, (void (*)(void *))delete_env);
		exit(ms()->exit);
	}
}
