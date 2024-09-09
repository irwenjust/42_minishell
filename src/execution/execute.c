/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:44:05 by likong            #+#    #+#             */
/*   Updated: 2024/09/09 16:09:09 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_command(char **cmds)
{
	// if (!is_builtin(cmds[0]))
	// 	exec_others(cmds);
	if (!ft_strcmp(cmds[0], "exit") && ms()->cmd_nb == 1)
		ft_exit(cmds);
	else if (!ft_strcmp(cmds[0], "pwd") && matrix_size(cmds) == 1)
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp(cmds[0], "env") && matrix_size(cmds) == 1)
		print_env();
}

//missed signal function
static pid_t	handle_child(t_ast *node)
{
	pid_t	pid;

	pid = fork();
	(void)node;
	if (pid < 0)
	{
		ft_putstr_fd("Some mistake happend when fork process.\n", 2);
		restart(true);
	}
	else if (pid == 0)
	{
		//didn't check in_fd and out_fd here
		if (ms()->cmd_nb < 2)
			return ;
		if (ms()->in_fd = STD_IN)
			if (node->index != 0)
				
	}
	return (pid);
}

static pid_t	fill_pipe(t_ast *node)
{
	pid_t	pid;

	pid = 0;
	if (!node)
		return (pid);
	pid = fill_pipe(node->left);
	pid = fill_pipe(node->right);
	if (!is_redir(node->token))
	{
		if (is_unfork(node->arg[0], node->arg[1]))
			handle_command(node->arg);
		else
			pid = handle_child(node);
			printf("next\n");
	}
	// else if (is_redir(node->token))
	// 	redirect(node->token->type, node->arg[0]);
	return (pid);
}

//missed signal function
void	execute(t_ast *ast)
{
	// pid_t	pid;

	create_pipe();
	fill_pipe(ast);
}
