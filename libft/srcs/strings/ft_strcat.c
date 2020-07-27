/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:20:14 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/17 12:07:04 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

char		*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = -1;
	while (s2[++j])
		s1[i + j] = s2[j];
	s1[i + j] = '\0';
	return (s1);
}
