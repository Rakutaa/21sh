/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arriter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:18:03 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/16 21:03:52 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void		ft_arriter(char **arr, void (*f)(const char *))
{
	size_t	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		(*f)(arr[i]);
}
