/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:27:54 by likong            #+#    #+#             */
/*   Updated: 2024/09/11 12:25:42 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*jump_to_newline(char *content)
{
	char	*new_content;
	char	*res;
	int		len;

	res = str_chr(content, '\n');
	if (!res)
	{
		new_content = NULL;
		return (f_free(&content));
	}
	else
		len = (res - content) + 1;
	if (!content[len])
		return (f_free(&content));
	new_content = substr(content, len, str_leng(content, '\0') - len);
	f_free(&content);
	if (!new_content)
		return (NULL);
	return (new_content);
}

// check and generate new string as end by '\n'
char	*check_line(char *content)
{
	char	*line;
	size_t	len;

	len = str_leng(content, '\n');
	if (content[len] == '\n')
		len++;
	line = substr(content, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

// get the content from file, end by '\n' or to the end
char	*get_content(int fd, char *content)
{
	char	*content_buf;
	ssize_t	bytes;

	bytes = 1;
	content_buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!content_buf)
		return (f_free(&content));
	while ((content && bytes > 0 && !str_chr(content, '\n')) || !content)
	{
		bytes = read(fd, content_buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(content_buf);
			return (f_free(&content));
		}
		if (bytes == 0)
			break ;
		content_buf[bytes] = '\0';
		content = str_join(content, content_buf);
	}
	free(content_buf);
	if (str_leng(content, '\0') > 0)
		return (content);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*content[1024];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024)
		return (NULL);
	content[fd] = get_content(fd, content[fd]);
	if (!content[fd])
		return (NULL);
	line = check_line(content[fd]);
	if (!line)
		return (f_free(&content[fd]));
	content[fd] = jump_to_newline(content[fd]);
	return (line);
}
