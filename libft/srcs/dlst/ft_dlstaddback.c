/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstaddback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:25:51 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/24 21:59:27 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlst.h"

void		ft_dlstaddback(t_dlist **alst, t_dlist *new)
{
	t_dlist	*current;

	if (!alst || !new)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		current = *alst;
		while (current->next)
			current = current->next;
		current->next = new;
		current->next->prev = current;
	}
}
