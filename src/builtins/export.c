/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:02:34 by likong            #+#    #+#             */
/*   Updated: 2024/09/17 13:58:56 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_all_env(void)
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

void	find_envtmp(char *key)
{
	t_env	*env;
	t_env	*tmp;

	tmp = find_env(ms()->local_var, key);
	if (!tmp)
		return ;
	env = find_env(ms()->env_list, key);
	if (env)
	{
		ft_free(env->value);
		env->value = ft_strdup(tmp->value);
	}
	else
		ft_lstadd_front(&ms()->env_list, ft_lstnew(copy_env(tmp)));
}

void	ft_export(char **args)
{
	int		i;
	t_token	*tmp;

	if (matrix_size(args) == 1)
		print_all_env();
	i = 0;
	while (args[++i])
	{
		tmp = token_new(args[i], TK_KEYWORD, false);
		if (((tmp->tk[0] - '0') >= 0 && (tmp->tk[0] - '0') <= 9)
			|| !ft_strchr_sep(tmp->tk, '-', '=') || tmp->tk[0] == '=')
		{
			ft_putstr_fd("minishell: export: `", STD_ERR);
			ft_putstr_fd(args[i], STD_ERR);
			ft_putstr_fd("': not a valid identifier\n", STD_ERR);
			ms()->exit = 1;
			continue ;
		}
		if (is_local_variable(tmp))
			add_node_for_local(&ms()->env_list, args[i]);
		else
			find_envtmp(args[i]);
		ft_free(tmp);
	}
	ms()->exit = 0;
}
