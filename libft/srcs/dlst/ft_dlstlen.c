/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:04:11 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/24 21:55:42 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlst.h"

size_t		ft_dlstlen(t_dlist **alst)
{
	size_t	i;
	t_dlist	*current;

	if (!alst)
		return (0);
	i = 0;
	current = *alst;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
