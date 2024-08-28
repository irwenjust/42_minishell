/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:17:47 by likong            #+#    #+#             */
/*   Updated: 2024/07/25 08:28:03 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*clean_work(t_list	**res, void (*del)(void *))
{
	ft_lstclear(res, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*list_node;
	void	*list_content;

	if (!lst || !f || !del)
		return (NULL);
	res = NULL;
	while (lst)
	{
		list_content = f(lst->content);
		if (!list_content)
			return (clean_work(&res, del));
		list_node = ft_lstnew(list_content);
		if (!list_node)
		{
			del(list_content);
			return (clean_work(&res, del));
		}
		ft_lstadd_back(&res, list_node);
		lst = lst->next;
	}
	return (res);
}
