/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:55:18 by likong            #+#    #+#             */
/*   Updated: 2024/09/13 15:34:05 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	matrix_size(char **matrix)
{
	size_t	i;

	if (!matrix)
		return (0);
	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

char	**matrix_add(char **matrix, char *str)
{
	char	**res;
	size_t	i;

	i = 0;
	res = ft_calloc(matrix_size(matrix) + 2, sizeof(char *));
	if (!res)
		return (NULL);
	while (matrix[i])
	{
		res[i] = ft_strdup(matrix[i]);
		i++;
	}
	res[i] = str;
	matrix_delete(matrix);
	return (res);
}

void	matrix_delete(void *matrix)
{
	size_t	i;
	char	**mat;

	if (!matrix)
		return ;
	i = -1;
	mat = (char **)matrix;
	while (mat[++i])
		ft_free(mat[i]);
	ft_free(matrix);
}
