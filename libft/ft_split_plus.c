/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 08:51:22 by likong            #+#    #+#             */
/*   Updated: 2024/08/06 17:01:39 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*push_str(t_str save)
{
	size_t	len;
	char	*res;

	len = save.end - save.start;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, save.start, len + 1);
	res[len] = '\0';
	return (res);
}

static void	find_next_quote(t_str *save, char **str)
{
	char	*res;

	res = ft_strchr(*str + 1, '\'');
	while (res && res[-1] == '\\')
		res = ft_strchr(res + 1, '\'');
	if (res)
	{
		save->start++;
		save->end = res;
		*str = res + 1;
	}
}

static t_str	catch_str(char **str, char c)
{
	t_str	save;

	save.start = NULL;
	save.end = NULL;
	while (**str && **str == c)
		(*str)++;
	if (!**str)
		return (save);
	save.start = *str;
	while (**str && **str != c)
	{
		if (**str == '\'')
		{
			find_next_quote(&save, str);
			if (save.end != NULL)
				return (save);
		}
		(*str)++;
	}
	save.end = *str;
	return (save);
}

static size_t	count_words(char *str, char c)
{
	int		count;
	t_str	save;

	save = catch_str(&str, c);
	count = 0;
	while (save.start != NULL)
	{
		save = catch_str(&str, c);
		count++;
	}
	return (count);
}

char	**split_plus(char *str, char c)
{
	char	**strs;
	size_t	i;
	t_str	save;

	if (!str)
		return (NULL);
	strs = (char **)malloc((count_words(str, c) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	save = catch_str(&str, c);
	i = 0;
	while (save.start != NULL)
	{
		strs[i] = push_str(save);
		if (!strs[i])
		{
			free_matrix(strs);
			return (NULL);
		}
		save = catch_str(&str, c);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
