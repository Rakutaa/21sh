/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:07:07 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/25 00:32:11 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "strings.h"
#include "numbers.h"
#include "swap.h"

static char			*parse_p_padding(char *p, t_memo *memo)
{
	int				i;
	char			*tmp;
	char			*ad;
	char			c;

	if (!memo->width || (0 > (i = ft_atoi(memo->width) - ft_strlen(p))))
		return (p);
	c = ' ';
	memo->zero && !memo->minus ? c = '0' : 0;
	ad = ft_strnew(i);
	while (i > 0)
		ad[--i] = c;
	tmp = p;
	if (memo->minus)
		p = ft_strjoin(p, ad);
	else
	{
		ad[0] == '0' && ad[1] && p[1] == 'x' ? ft_swap_char(&p[1], &ad[1]) : 0;
		ad[0] == '0' && !ad[1] && p[1] == 'x' ? ft_swap_char(&p[1], &p[0]) : 0;
		p = ft_strjoin(ad, p);
	}
	free(ad);
	free(tmp);
	return (p);
}

int					parse_p(va_list last, t_memo *memo)
{
	char			*tmp;
	char			*print;

	tmp = ft_itoa_base(va_arg(last, unsigned long long), 16);
	if (tmp[0] == '0' && memo->precision && !ft_atoi(memo->precision + 1))
		tmp[0] = '\0';
	print = ft_strjoin("0x", tmp);
	free(tmp);
	print = parse_p_padding(print, memo);
	return (putprint(print, memo->fd));
}
