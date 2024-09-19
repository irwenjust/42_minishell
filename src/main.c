/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:46:00 by likong            #+#    #+#             */
/*   Updated: 2024/09/19 17:31:17 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Didn't handle the exit status, only std_err right now
static void	init_ms(char **envp)
{
	char	*res;

	ft_bzero(ms(), sizeof(t_ms));
	(ms()->in_fd) = STD_IN;
	(ms()->out_fd) = STD_OUT;
	(ms()->exit) = 0;
	(ms()->last_pid) = 0;
	(ms()->lines) = 0;
	(ms()->cwd) = getcwd(NULL, 2048);
	if (!(ms()->cwd))
	{
		perror("getcwd() error");
		exit(1);
	}
	(ms()->env_list) = init_list(envp);
	res = get_env("PATH");
	(ms()->path) = ft_split(res, ':');
	(ms()->envp) = list_to_arr(ms()->env_list);
	free(res);
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
	signal_default();
	start_shell();
	return (0);
}
