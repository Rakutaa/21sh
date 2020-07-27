/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:35:29 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/16 19:54:45 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*node;
	t_list	*begin;

	if (!lst || !f)
		return (NULL);
	node = f(lst);
	begin = node;
	while (lst->next)
	{
		lst = lst->next;
		if (!(node->next = f(lst)))
			return (NULL);
		node = node->next;
	}
	return (begin);
}
