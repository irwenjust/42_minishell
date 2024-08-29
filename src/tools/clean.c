/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:23:09 by likong            #+#    #+#             */
/*   Updated: 2024/08/29 19:22:23 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *p)
{
	if (p)
		free(p);
	p = NULL;
}

void	delete_matrix(void *matrix)
{
	size_t	i;
	char	**res;

	if (!matrix)
		return ;
	i = -1;
	res = (char **)matrix;
	while (res[++i])
		ft_free(res[i]);
	ft_free(matrix);
}

void	delete_env(t_env *env)
{
	ft_free(env->key);
	ft_free(env->value);
	ft_free(env);
}

void	clean_all(bool status)
{
	ft_free(ms()->prompt);
	ft_free(ms()->input);
	if (status)
	{
		ft_free(ms()->cwd);
		delete_matrix(ms()->path);
		delete_matrix(ms()->envp);           //??????????????????
		ft_lstclear(&ms()->env_list, (void (*)(void *))delete_env);
		exit(ms()->exit);
	}
}
