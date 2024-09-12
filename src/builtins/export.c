/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:02:34 by likong            #+#    #+#             */
/*   Updated: 2024/09/12 20:28:18 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_all_env()
{
	t_env	*env;
	t_list	*tmp;

	tmp = ms()->env_list;
	while (tmp)
	{
		env = tmp->content;
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		tmp = tmp->next;
	}
	tmp = ms()->local_var;
	while (tmp)
	{
		env = tmp->content;
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		tmp = tmp->next;
	}
}

void	ft_export(char **args)
{
	if (matrix_size(args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ms()->exit = 1;
		return ;
	}
	else if (matrix_size(args) == 1)
		print_all_env();
	
}
