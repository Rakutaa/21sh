/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:31:21 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/15 14:35:48 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlst.h"

void	ft_dlstiter(t_dlist *dlst, void (*f)(t_dlist *elem))
{
	if (!dlst || !f)
		return ;
	while (dlst)
	{
		f(dlst);
		dlst = dlst->next;
	}
}
