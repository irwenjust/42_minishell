/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:13:39 by likong            #+#    #+#             */
/*   Updated: 2024/09/11 12:31:37 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*expand_line(char *line)
// {
// 	char	*
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
		write(1, "> ", 2);
		line = get_next_line(STD_IN);
		if (!line)
		{
			close(fd);
			show_error(NULL, NEXT_LINE, FAIL_STD);
		}
		if (!ft_strcmp(line, end_of_file))
			break ;
		// line = expand_line(line);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	ft_free(line);
	restart(true);
}

//Didn't handle signal part
static int	start_heredoc(char *f_name)
{
	pid_t	pid;
	
	if (ms()->in_fd > STD_IN)
		close(ms()->in_fd);
	pid = fork();
	if (pid < 0)
		show_error(NULL, FORK, FAIL_STD);
	else if (pid == 0)
		read_heredoc(f_name);
	waitpid(0, NULL, 0);
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
