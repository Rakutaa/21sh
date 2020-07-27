/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 10:56:06 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/17 12:02:45 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

void		ft_arrfree(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		ft_strdel(&arr[i]);
	free(arr);
}
