/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:17:07 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/26 00:44:46 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

char		*ft_strnew(size_t size)
{
	char	*area;

	area = (char *)malloc(sizeof(char) * (size + 1));
	if (!area)
		return (NULL);
	ft_memset(area, '\0', (size + 1));
	return (area);
}
