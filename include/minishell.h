/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:56:57 by likong            #+#    #+#             */
/*   Updated: 2024/08/29 18:53:48 by likong           ###   ########.fr       */
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

/*
stdio: printf()
unistd: getcwd()
stdlib: perror()
errno: errno
readline: readline
stdbool: bool function
*/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
// # include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>

# include "libft.h"
# include "ft_printf/ft_printf.h"

typedef struct	s_env
{
	char	*key;
	char	*value;
}	t_env;

/*
in_fd: fd for input
out_fd: fd for output
exit: exit status when leave program, like 0, 1, 126, 127
cwd: current working directory. similar than pwd(print working directory)
path: save path environment variable
envp: whole environment variable
env_list: save environment to link list
*/
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
	t_list	*lexer_tk;
}	t_ms;

/*
token type for lexer
TK_PIPE: pipes |
TK_IN_RE/TK_OUT_RE: redirection </>
TK_HEREDOC: <<
TK_APPEND: >>
TK_SINGLE_QT/TK_DOUBLE_QT: single quote''/double quote ""
TK_END: end of command
*/
typedef enum e_token_type
{
	TK_PIPE,
	TK_IN_RE,
	TK_OUT_RE,
	TK_HEREDOC,
	TK_APPEND,
	TK_SINGLE_QT,
	TK_DOUBLE_QT,
	TK_KEYWORD, //?????
}	t_token_type;

typedef enum e_token_manager
{
	RESET,
	CURRENT,
	NEXT,
	PREVIEW,
} t_manager;

typedef struct s_token
{
	char *input;
	t_token_type type;
	bool mergeable;
}	t_token;



//Create ms struct
t_ms	*ms(void);

//Shell interface
void	start_shell(void);

//Pre Handling
//Lexer
bool check_quote(void);
void lexer(void);
bool check_syntax(void);

//token manager
int add_token(char *str, t_token_type type, bool merge);
void delete_token(t_token *token);
t_token *token_manager(t_manager mg);

//Expander
void expander(void);

//Parser
void	start_parse(void);

//handler utils
bool is_redir_or_pipe(t_token *token);
bool is_redirection(t_token *token);


//For environment
// void	update_env(void);
t_env	*new_env(char *key, char *value);
char	*get_env(char *key);
void	print_env(void);

//Delete and clean function
void	delete_matrix(void *matrix);
void	ft_free(void *p);
void	delete_env(t_env *env);
void	clean_all(bool status);

//Matrix function
size_t	matrix_size(char **strs);

//Link list function
char	**list_to_arr(t_list *list);
t_list	*init_list(char **strs);
void	add_node(t_list **list, char *str);

//Utils function
int	str_len(char *str, char *sep);
int error_info(char *info);









//Exit function
void	ft_exit(char **strs);

//signal
void singal_default(void);

#endif
