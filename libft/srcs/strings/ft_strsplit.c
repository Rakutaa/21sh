/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:48:17 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/17 12:08:14 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

static int	ft_len(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			return (count);
		count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	j;
	size_t	stopper;

	if (!s || !(array = (char **)malloc(sizeof(char *)
	* ft_len(s, c) + sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		stopper = i;
		if (!s[i])
			break ;
		while (s[i] != c && s[i])
			i++;
		array[j] = ft_strsub(s, stopper, i - stopper);
		j++;
	}
	array[j] = NULL;
	return (array);
}
