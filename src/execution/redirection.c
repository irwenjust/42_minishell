/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:13:39 by likong            #+#    #+#             */
/*   Updated: 2024/09/19 17:43:02 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_line(char *input, int fd)
{
	char	*expanded;
	char	*value;
	char	*key;
	char	*tmp;

	expanded = ft_strdup(input);
	while (ft_strnstr(expanded, "$", ft_strlen(expanded)))
	{
		key = find_keyword(expanded);
		if (!ft_strcmp(key, "$?"))
			value = ft_itoa(ms()->exit);
		else
			value = get_env(key);
		tmp = expanded;
		expanded = ft_strreplace(expanded, key, value);
		ft_free(tmp);
		ft_free(value);
		ft_free(key);
	}
	ft_putendl_fd(input, fd);
	ft_free(input);
	return (expanded);
}

static void	heredoc_error(char *eof)
{
	char	*num;

	num = ft_itoa(ms()->lines);
	if (!num)
		num = NULL;
	ft_putstr_fd("bash: warning: here-document at line ", STD_ERR);
	ft_putstr_fd(num, STD_ERR);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STD_ERR);
	ft_putstr_fd(eof, STD_ERR);
	ft_putstr_fd("')\n", STD_ERR);
	ms()->exit = FAIL_STD;
}

static void	read_heredoc(char *end_of_file)
{
	int		fd;
	char	*line;

	fd = open("here_doc", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		ft_err(NULL, HERE_DOC, FAIL_STD);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			heredoc_error(end_of_file);
			break ;
		}
		if (!ft_strcmp(line, end_of_file))
		{
			ft_free(line);
			break ;
		}
		line = expand_line(line, fd);
		free(line);
	}
	close(fd);
	restart(true);
}

static int	start_heredoc(char *f_name)
{
	pid_t	pid;

	signal_heredoc();
	if (ms()->in_fd > STD_IN)
		close(ms()->in_fd);
	pid = fork();
	if (pid < 0)
		ft_err(NULL, FORK, FAIL_STD);
	else if (pid == 0)
		read_heredoc(f_name);
	signal_ignore();
	waitpid(0, NULL, 0);
	signal_default();
	return (open("here_doc", O_RDONLY, 0444));
}

int	redirect(t_token_type type, char *f_name)
{
	if (type == TK_IN_RE)
		(ms()->in_fd) = open(f_name, O_RDONLY, 0444);
	else if (type == TK_HDOC)
		(ms()->in_fd) = start_heredoc(f_name);
	else if (type == TK_OUT_RE)
		(ms()->out_fd) = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == TK_APPEND)
		(ms()->out_fd) = open(f_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (ms()->in_fd == -1 || ms()->out_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		if (!access(f_name, F_OK))
			ft_err(f_name, PERMISSION, FAIL_STD);
		else
			ft_err(f_name, FILE_NAME, FAIL_STD);
		restart(true);
	}
	return (0);
}
