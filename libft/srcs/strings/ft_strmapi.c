/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:16:50 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/17 12:07:47 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fresh;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	fresh = ft_strnew(ft_strlen(s));
	if (!fresh)
		return (NULL);
	i = -1;
	while (s[++i])
		fresh[i] = (*f)(i, s[i]);
	fresh[i] = '\0';
	return (fresh);
}
