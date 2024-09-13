/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:42:17 by likong            #+#    #+#             */
/*   Updated: 2024/09/13 11:42:34 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_remove_if_aux(t_list *node, void *ref, \
	bool (*cmp)(), void (*f)())
{
	t_list	*ret;

	if (!node)
		return (NULL);
	if ((*cmp)(node->content, ref))
	{
		ret = ft_list_remove_if_aux(node->next, ref, cmp, f);
		if (*f)
			(*f)(node->content);
		free(node);
	}
	else
	{
		ret = node;
		ret->next = ft_list_remove_if_aux(node->next, ref, cmp, f);
	}
	return (ret);
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, \
	bool (*cmp)(), void (*free_fct)())
{
	if (!begin_list || !cmp)
		return ;
	*begin_list = ft_list_remove_if_aux(*begin_list, data_ref, cmp, free_fct);
}
