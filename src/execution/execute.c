#include "minishell.h"

void	execute(void)
{
	char	**cmds;

	cmds = split_plus(ms()->input, ' ');
	if (!cmds)
		return ;
	if (!ft_strcmp(cmds[0], "exit"))
		ft_exit(cmds);
	else if (!ft_strcmp(cmds[0], "pwd") && matrix_size(cmds) == 1)
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp(cmds[0], "env") && matrix_size(cmds) == 1)
		print_env();
	delete_matrix(cmds);
}