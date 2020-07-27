/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:15:12 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/26 00:41:01 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void		*ft_memalloc(size_t size)
{
	void	*area;

	area = (void *)malloc(size);
	if (!area)
		return (NULL);
	ft_bzero(area, size);
	return (area);
}
