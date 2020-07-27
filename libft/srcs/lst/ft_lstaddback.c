/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:25:51 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/22 13:14:30 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void		ft_lstaddback(t_list **alst, t_list *new)
{
	t_list	*cur_list;

	if (!alst || !new)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		cur_list = *alst;
		while (cur_list->next)
			cur_list = cur_list->next;
		cur_list->next = new;
	}
}
