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
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>

# include "libft.h"
# include "ft_printf/ft_printf.h"

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

/*
token list manager
RESET: reset to the first one
CURRENT: current token
NEXT: move to next token
PREVIEW: get the content of next token without move to it.
*/
typedef enum e_token_manager
{
	RESET,
	CUR,
	NEXT,
	PREVIEW,
} t_manager;

/*
token struct
input: input from cmdline
type: token type(pipe, redirection or other)
mergeabel: can be merged with next token or not*/
typedef struct s_token
{
	char *tk;
	t_token_type type;
	bool mergeable;
}	t_token;

/*
abstract syntax tree
*/
typedef struct s_ast
{
	t_token *token;
	char **arg;
	int index;
	struct s_ast *left;
	struct s_ast *right;
} t_ast;

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
lexer_tk: token get from lexer process
ast: abstract syntax tess from parse process
*/
typedef struct	s_ms
{
	int		in_fd;
	int		out_fd;
	int		exit;
	int		cmd_nb;
	char	*cwd;
	char	*prompt;
	char	*input;
	char	**path;
	char	**envp;
	t_list	*env_list;
	t_list	*lexer_tk;
	t_ast *ast;
}	t_ms;




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
t_token *token_new(char *input, t_token_type type, bool mergeable);
int token_add(char *str, t_token_type type, bool merge);
t_token *token_copy(t_token *token);
void token_delete(t_token *token);
t_token *token_manager(t_manager mg);

//Expander
void expander(void);

//Parser
void	parser(void);

//ast
t_ast *ast_new(t_token *token);
void ast_insert(t_ast **ast, t_ast *node, bool left);
void ast_delone(t_ast *ast);
void ast_clear(t_ast *ast, void (*del)(t_ast *));

//handler utils
bool is_redir_or_pipe(t_token *token);
bool is_redir(t_token *token);
bool	is_pipe(t_token *token);

//For environment
// void	update_env(void);
t_env	*new_env(char *key, char *value);
char	*get_env(char *key);
void	print_env(void);

//Delete and clean function
void	ft_free(void *p);
void	delete_env(t_env *env);
void	restart(bool status);

//Matrix function
size_t	matrix_size(char **matrix);
char **matrix_add(char **matrix, char *str);
void	matrix_delete(void *matrix);

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
