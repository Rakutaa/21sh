/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_upper_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:19:15 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/25 00:31:49 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ctypes.h"
#include "strings.h"
#include "numbers.h"
#include "swap.h"

static char			*parse_upper_x_padding(char *p, t_memo *memo)
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

static char			*parse_upper_x_precision(char *print, t_memo *memo)
{
	size_t			i;
	char			*buffer;
	char			*tmp;

	if (!memo->precision)
		return (print);
	i = ft_atoi(memo->precision + 1);
	if (i > ft_strlen(print))
	{
		i = i - ft_strlen(print);
		buffer = ft_strnew(i);
		while (i > 0)
			buffer[--i] = '0';
		tmp = print;
		print = ft_strjoin(buffer, print);
		free(tmp);
		free(buffer);
	}
	else if (print[0] == '0' && !memo->hash)
		print[0] = '\0';
	memo->zero ? memo->zero = 0 : 0;
	return (print);
}

static char			*parse_upper_x_signs(char *print, t_memo *memo)
{
	char			*tmp;

	if (memo->hash)
	{
		tmp = print;
		print = ft_strjoin("0x", print);
		free(tmp);
	}
	return (print);
}

static char			*parse_upper_x_length(va_list last, t_memo *memo)
{
	char			*pos;

	if ((pos = ft_strchr(memo->length, 'h')))
	{
		if (*(pos + 1) == 'h')
			return (ft_itoa_base((unsigned char)
					va_arg(last, unsigned int), 16));
		else
			return (ft_itoa_base((unsigned short int)
					va_arg(last, unsigned int), 16));
	}
	if ((pos = ft_strchr(memo->length, 'l')))
	{
		if (*(pos + 1) == 'l')
			return (ft_itoa_base((unsigned long long)
					va_arg(last, unsigned long long), 16));
		else
			return (ft_itoa_base((unsigned long)
					va_arg(last, unsigned long), 16));
	}
	return (ft_itoa_base((unsigned int)va_arg(last, unsigned int), 16));
}

int					parse_upper_x(va_list last, t_memo *memo)
{
	char			*print;
	int				i;

	print = parse_upper_x_length(last, memo);
	if (print[0] == '0')
		memo->hash = 0;
	print = parse_upper_x_precision(print, memo);
	print = parse_upper_x_signs(print, memo);
	print = parse_upper_x_padding(print, memo);
	i = 0;
	while (print[i])
	{
		print[i] = ft_toupper(print[i]);
		i++;
	}
	return (putprint(print, memo->fd));
}
