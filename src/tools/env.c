/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:21:36 by likong            #+#    #+#             */
/*   Updated: 2024/08/29 19:27:20 by likong           ###   ########.fr       */
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

//didn't consider doller sidn still. $
char	*get_env(char *key)
{
	t_env	*res;
	t_list	*curr;

	curr = ms()->env_list;
	while (curr)
	{
		res = (t_env *)curr->content;
		if (!ft_strcmp(res->key, key))
			return (ft_strdup(res->value));
		curr = curr->next;
	}
	return (ft_strdup(""));
}

// void	update_env(void)
// {
// 	char	*res;

// 	delete_matrix(ms()->path);
// 	delete_matrix(ms()->envp);
// 	res = get_env("PATH");
	
// }

void	print_env(void)
{
	int	i;

	i = -1;
	while (ms()->envp[++i])
		printf("%s\n", ms()->envp[i]);
}
