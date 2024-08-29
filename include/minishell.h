/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:56:57 by likong            #+#    #+#             */
/*   Updated: 2024/08/29 14:27:43 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

# define SUCCESS 0
# define FAIL_STD 1
# define FAIL_EXEC 126
# define FAIL_FCMD 127

//stdio: printf()
//unistd: getcwd()
//stdlib: perror()
//errno: errno
//readline: readline
//stdbool: bool function
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
// # include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# include "libft.h"
# include "ft_printf/ft_printf.h"

typedef struct	s_env
{
	char	*key;
	char	*value;
}	t_env;

//in_fd: fd for input
//out_fd: fd for output
//exit: exit status when leave program, like 0, 1, 126, 127
//cwd: current working directory. similar than pwd(print working directory)
//path: save path environment variable
//envp: whole environment variable
//env_list: save environment to link list
typedef struct	s_ms
{
	int		in_fd;
	int		out_fd;
	int		exit;
	char	*cwd;
	char	*prompt;
	char	*input;
	char	**path;
	char	**envp;
	t_list	*env_list;
}	t_ms;

//Create ms struct
t_ms	*ms(void);

//For environment
void	update_env(void);
t_env	*new_env(char *key, char *value);
char	*get_env(char *key);

//Delete and clean function
void	delete_matrix(void *matrix);
void	ft_free(void *p);
void	delete_env(t_env *env);
void	clean_all(bool status);

//Matrix function
size_t	matrix_size(char **strs);

//Utils function
int	str_len(char *str, char *sep);

//Shell interface
void	start_shell(void);

//Parser part
void	start_parse(void);

//Exit function
void	ft_exit(char **strs);

#endif
