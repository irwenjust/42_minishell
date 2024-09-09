/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:58:49 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/09 14:58:51 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(char *path)
{
	char *newpwd;

	if (!ft_strcmp(path, "")) //why not just !path????
		error_info("error cd no home.\n");
	newpwd = "OLDPWD=";
	newpwd = ft_strjoin(newpwd, ms()->cwd);
	//update old pwd which is current one
	export_dir(&ms()->env_list, newpwd);
	free(newpwd);
	//default func chdir to change the dir
	chdir(path);
	free(ms()->cwd);
	(ms()->cwd) = getcwd(NULL, 4096);
	newpwd = "PWD=";
	newpwd = ft_strjoin(newpwd, ms()->cwd);
	//update cur pwd env
	export_dir(&ms()->env_list, newpwd);
	free(newpwd);
	free(path);
}

/*
S_ISDIR is a macro defined in <sys/stat.h> used to check whether 
a file is a directory. 
The macro takes the st_mode value as an argument and checks 
if the file type corresponds to a directory.
*/
void ft_cd(char **token)
{
	struct stat cur_stat;

	if (matrix_size(token) > 1)
	{
		error_info("too many args\n");
		return ;
	}
	//if no arg or arg[0] is ~, cd to HOME dir
	if (!token[0] || !ft_strcmp(token[0], "~"))
	{
		change_dir(get_env("HOME"));
		return ;
	}
	//stat() system call to retrieve information about the file 
	//or directory specified by token[0] (the target directory).
	stat(token[0], &cur_stat);
	//check target path is dir or not, with st_mode
	if (S_ISDIR(cur_stat.st_mode))
		change_dir(ft_strdup(token[0]));
	else
		error_info("127\n");
}
