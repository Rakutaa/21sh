/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:25:39 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/26 00:41:25 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int						ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*cs1;
	const unsigned char	*cs2;

	i = -1;
	cs1 = (const unsigned char*)s1;
	cs2 = (const unsigned char*)s2;
	while (++i < n)
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
	return (0);
}
