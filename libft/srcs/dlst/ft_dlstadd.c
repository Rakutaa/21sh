/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:26:36 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/24 23:24:16 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlst.h"

void	ft_dlstadd(t_dlist **alst, t_dlist *new)
{
	if (!alst || !new)
		return ;
	if (*alst)
		(*alst)->prev = new;
	new->next = *alst;
	*alst = new;
}
