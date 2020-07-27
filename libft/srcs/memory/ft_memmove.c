/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:23:46 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/26 00:41:55 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void					*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	const unsigned char	*csrc;
	unsigned char		*cdst;

	i = 0;
	csrc = (const unsigned char*)src;
	cdst = (unsigned char*)dst;
	if (cdst > csrc)
		while (0 < len)
		{
			cdst[len - 1] = csrc[len - 1];
			len--;
		}
	else
		while (i < len)
		{
			cdst[i] = csrc[i];
			i++;
		}
	return (dst);
}
