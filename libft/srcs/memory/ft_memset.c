/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:27:57 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/26 00:42:02 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void				*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*buff;
	size_t			i;

	buff = (unsigned char*)b;
	i = -1;
	while (++i < len)
		buff[i] = c;
	return (b);
}
