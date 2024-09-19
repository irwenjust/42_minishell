/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:21:36 by likong            #+#    #+#             */
/*   Updated: 2024/09/19 12:17:59 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*res;

	res = (t_env *)malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	res->key = key;
	res->value = value;
	return (res);
}

t_env	*copy_env(t_env	*env)
{
	t_env	*res;

	res = new_env(ft_strdup(env->key), ft_strdup(env->value));
	if (!res)
		return (NULL);
	return (res);
}

char	*get_env(char *key)
{
	t_env	*tmp;
	t_list	*curr;

	if (key[0] == '$')
		key++;
	curr = ms()->env_list;
	while (curr)
	{
		tmp = (t_env *)curr->content;
		if (!ft_strcmp(tmp->key, key))
			return (ft_strdup(tmp->value));
		curr = curr->next;
	}
	return (ft_strdup(""));
}

t_env	*find_env(t_list *envs, char *key)
{
	t_list	*curr;
	t_env	*env;

	if (!envs)
		return (NULL);
	curr = envs;
	while (curr)
	{
		env = (t_env *)curr->content;
		if (!ft_strcmp(env->key, key))
			return (env);
		curr = curr->next;
	}
	return (NULL);
}

void	update_env(void)
{
	char	*res;

	matrix_delete(ms()->path);
	matrix_delete(ms()->envp);
	res = get_env("PATH");
	(ms()->path) = ft_split(res, ':');
	(ms()->envp) = list_to_arr(ms()->env_list);
	free(res);
}
