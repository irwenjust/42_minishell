/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:58:49 by yzhan             #+#    #+#             */
/*   Updated: 2024/09/13 15:20:42 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_list **env_list, char *newpwd)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*env;

	i = ft_strlen_sep(newpwd, "=");
	name = ft_substr(newpwd, 0, i);
	value = ft_strdup(newpwd + i + 1);
	env = find_env(*env_list, name);
	if (env)
	{
		free(name);
		free(env->value);
		env->value = value;
	}
	else
		ft_lstadd_front(env_list, ft_lstnew(new_env(name, value)));
}

void	change_dir(char *path)
{
	char	*newpwd;

	if (!ft_strcmp(path, ""))
		ft_err("error cd no home.", -1, STD_ERR);
	newpwd = "OLDPWD=";
	newpwd = ft_strjoin(newpwd, ms()->cwd);
	update_pwd(&ms()->env_list, newpwd);
	free(newpwd);
	chdir(path);
	free(ms()->cwd);
	(ms()->cwd) = getcwd(NULL, 4096);
	newpwd = "PWD=";
	newpwd = ft_strjoin(newpwd, ms()->cwd);
	update_pwd(&ms()->env_list, newpwd);
	free(newpwd);
	free(path);
}

/*
S_ISDIR is a macro defined in <sys/stat.h> used to check whether 
a file is a directory. 
The macro takes the st_mode value as an argument and checks 
if the file type corresponds to a directory.
*/
void	ft_cd(char **token)
{
	struct stat	cur_stat;

	if (matrix_size(token) > 2)
	{
		ft_err("cd: too many arguments", -1, FAIL_STD);
		return ;
	}
	if (!token[1] || !ft_strcmp(token[1], "~"))
	{
		change_dir(get_env("HOME"));
		return ;
	}
	stat(token[1], &cur_stat);
	if (S_ISDIR(cur_stat.st_mode))
		change_dir(ft_strdup(token[1]));
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(token[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ms()->exit = 1;
	}
}
