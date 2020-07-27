/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:48:32 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/17 12:07:20 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

char		*ft_strdup(const char *s1)
{
	size_t	i;
	char	*copy;

	copy = ft_strnew(ft_strlen(s1));
	if (!copy)
		return (NULL);
	i = -1;
	while (s1[++i])
		copy[i] = s1[i];
	copy[i] = '\0';
	return (copy);
}
