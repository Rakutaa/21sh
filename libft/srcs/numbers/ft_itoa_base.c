/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 11:22:49 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/17 12:05:36 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

static int	length(unsigned long long value, int base)
{
	int	len;

	len = 1;
	while (value /= base)
		len++;
	return (len);
}

static char	*reverse(char *str)
{
	char	*rev;
	int		i;
	int		j;

	if (!(rev = ft_strnew(ft_strlen(str))))
		return (NULL);
	i = 0;
	j = ft_strlen(str) - 1;
	while (str[i])
	{
		rev[i] = str[j];
		i++;
		j--;
	}
	free(str);
	return (rev);
}

static char	alpha(unsigned long long set)
{
	char	*alpha;

	alpha = "abcdef";
	return (alpha[set % 10]);
}

char		*ft_itoa_base(unsigned long long value, int base)
{
	char	*str;
	int		i;
	int		set;
	int		len;

	if (base < 2 || base > 16)
		return (NULL);
	len = length(value, base);
	if (!(str = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		set = value % base;
		if (set > 9)
			str[i] = alpha(set);
		else
			str[i] = set + '0';
		value /= base;
		i++;
	}
	return (reverse(str));
}
