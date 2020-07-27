/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:27:48 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/17 12:07:52 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

char		*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	i = ft_strlen(s1);
	while (s2[j] && n)
	{
		s1[i + j] = s2[j];
		j++;
		n--;
	}
	s1[i + j] = '\0';
	return (s1);
}
