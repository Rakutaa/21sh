/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:03:55 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/26 00:41:18 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void					*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*cs;

	i = -1;
	cs = (const unsigned char *)s;
	while (++i < n)
		if (cs[i] == c)
			return ((void *)s + i);
	return (NULL);
}
