/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:13:39 by likong            #+#    #+#             */
/*   Updated: 2024/09/11 15:59:15 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handler_heredoc(int signum)
// {
// 	if (signum != SIGINT)
// 		return ;
// 	printf("\n");
// 	restart(true);
// 	(ms()->exit) = 130;
// }

// void	signals_heredoc(void)
// {
// 	signal(SIGINT, handler_heredoc);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	signals_ignore(void)
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// }

// char	*ft_strreplace(char *str, char *old, char *new)
// {
// 	char	*ret;
// 	char	*tmp;
// 	char	*ptr;
// 	int		len;

// 	if (!str || !old || !new)
// 		return (NULL);
// 	len = ft_strlen(str) + ft_strlen(new) - ft_strlen(old);
// 	ret = ft_calloc(len + 1, sizeof(char));
// 	if (!ret)
// 		return (NULL);
// 	ptr = ft_strnstr(str, old, ft_strlen(str));
// 	if (!ptr)
// 		return (NULL);
// 	tmp = ft_substr(str, 0, ptr - str);
// 	ft_strlcat(ret, tmp, len + 1);
// 	ft_strlcat(ret, new, len + 1);
// 	ft_strlcat(ret, ptr + ft_strlen(old), len + 1);
// 	ft_free(tmp);
// 	return (ret);
// }

// char	*expand_line(char *input)
// {
// 	char	*expanded;
// 	char	*value;
// 	char	*key;
// 	char	*tmp;

// 	expanded = ft_strdup(input);
// 	while (ft_strnstr(expanded, "$", ft_strlen(expanded)))
// 	{
// 		key = find_keyword(expanded);
// 		if (!ft_strcmp(key, "$?"))
// 			value = ft_itoa(ms()->exit);
// 		else
// 			value = get_env(key);
// 		tmp = expanded;
// 		expanded = ft_strreplace(expanded, key, value);
// 		ft_free(tmp);
// 		ft_free(value);
// 		ft_free(key);
// 	}
// 	ft_free(input);
// 	return (expanded);
// }

//Use get_next_line to replace readline, 
//not sure work or not, check it later
static void	read_heredoc(char *end_of_file)
{
	int		fd;
	char	*line;

	fd = open("here_doc", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		show_error(NULL, HERE_DOC, FAIL_STD);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(1, "\n", 1);
			show_error(NULL, NEXT_LINE, FAIL_STD);
			break ;
		}
		if (!ft_strcmp(line, end_of_file))
		{
			ft_free(line);
			break ;
		}
		// line = expand_line(line);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	restart(true);
}

//Didn't handle signal part
static int	start_heredoc(char *f_name)
{
	pid_t	pid;

	// signals_heredoc();
	if (ms()->in_fd > STD_IN)
		close(ms()->in_fd);
	pid = fork();
	if (pid < 0)
		show_error(NULL, FORK, FAIL_STD);
	else if (pid == 0)
		read_heredoc(f_name);
	// signals_ignore();
	waitpid(0, NULL, 0);
	// signal_default();
	//The permission maybe need to adjust
	return (open("here_doc", O_RDONLY, 0444));
}

//The permission maybe need to adjust
void	redirect(t_token_type type, char *f_name)
{
	if (type == TK_IN_RE)
		(ms()->in_fd) = open(f_name, O_RDONLY, 0444);
	else if (type == TK_HEREDOC)
		(ms()->in_fd) = start_heredoc(f_name);
	else if (type == TK_OUT_RE)
		(ms()->out_fd) = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == TK_APPEND)
		(ms()->out_fd) = open(f_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (ms()->in_fd == -1 || ms()->out_fd == -1)
		show_error(f_name, FILE_NAME, FAIL_STD);
}
