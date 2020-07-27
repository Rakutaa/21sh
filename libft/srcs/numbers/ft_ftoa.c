/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:07:35 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/27 13:28:27 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"
#include "numbers.h"

static long double		round_decimal(int precision, long double f)
{
	long double			round;
	int					d;

	round = 0.5;
	if (f < 0)
		round *= -1;
	d = 0;
	while (d++ < precision)
		round /= 10.0;
	return (round);
}

static char				*fraction(int pre, long double f,
						unsigned long long dec)
{
	int					i;
	char				*fpart;

	fpart = ft_strnew(pre + 2);
	fpart[0] = '.';
	i = 1;
	while (pre-- > 0)
	{
		f *= 10;
		dec = f;
		f -= dec;
		fpart[i++] = dec + '0';
	}
	return (fpart);
}

char					*ft_ftoa(long double f, int pre)
{
	unsigned long long	dec;
	char				*ipart;
	char				*fpart;
	char				*joint;
	int					neg;

	neg = 0;
	f < 0 ? neg = 1 : 0;
	f = f + round_decimal(pre, f);
	f *= (f < 0) ? -1 : 1;
	dec = f;
	ipart = ft_itoa(dec);
	f = pre ? (f - dec) : 0;
	fpart = fraction(pre, f, dec);
	joint = ft_strjoin(ipart, fpart);
	free(ipart);
	free(fpart);
	if (neg)
	{
		ipart = joint;
		joint = ft_strjoin("-", joint);
		free(ipart);
	}
	return (joint);
}
