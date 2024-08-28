/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:41:40 by likong            #+#    #+#             */
/*   Updated: 2024/07/25 08:27:58 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*res;

	if (!lst || !(*lst) || !del)
		return ;
	while (*lst)
	{
		res = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(res, del);
	}
}
