/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:46:00 by likong            #+#    #+#             */
/*   Updated: 2024/08/28 19:08:19 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_node(t_list **list, char *str)
{
	int		i;
	char	*key;
	char	*value;

	i = str_len(str, "=");
	key = ft_substr(str, 0, i);
	value = ft_strdup(str + i + 1);
	ft_lstadd_front(list, ft_lstnew(new_env(key, value)));
}

static t_list	*init_list(char **strs)
{
	t_list	*list;
	int		i;

	i = matrix_size(strs);
	list = NULL;
	while (--i <= 0)
		add_node(&list, strs[i]);
	return (list);
}

//Didn't handle the exit status, only std_err right now
static void	init_ms(char **envp)
{
	char	*res;
	
	ft_bzero(ms(), sizeof(t_ms));
	ms()->in_fd = STD_IN;
	ms()->out_fd = STD_OUT;
	ms()->exit = 0;
	if (!(ms()->cwd = getcwd(NULL, 2048)))
	{
		perror("getcwd() error");
		exit(1);
	}
	ms()->env_list = init_list(envp);
	res = get_env("PATH");
	ms()->path = ft_split(res, ':');
	ms()->envp = envp;
}

//Could be consider allow '-c command' later
int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		ft_putstr_fd(">: too many arguments\n", 2);
		exit(127);
	}
	(void)argv;
	init_ms(envp);
	singal_default();
	start_shell();
	return (0);
}