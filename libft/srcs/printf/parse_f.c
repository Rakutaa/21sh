/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:18:05 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/25 00:27:52 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "strings.h"
#include "numbers.h"
#include "swap.h"

static char			*parse_f_padding(char *print, t_memo *memo)
{
	int				i;
	char			*tmp;
	char			*pad;
	char			c;

	if (!memo->width || (0 > (i = ft_atoi(memo->width) - ft_strlen(print))))
		return (print);
	c = ' ';
	memo->zero && !memo->minus ? c = '0' : 0;
	pad = ft_strnew(i);
	while (i > 0)
		pad[--i] = c;
	tmp = print;
	if (memo->minus)
		print = ft_strjoin(print, pad);
	else
	{
		print[0] == '-' && pad[0] == '0' ? ft_swap_char(&print[0], &pad[0]) : 0;
		print[0] == '+' && pad[0] == '0' ? ft_swap_char(&print[0], &pad[0]) : 0;
		print[0] == ' ' && pad[0] == '0' ? ft_swap_char(&print[0], &pad[0]) : 0;
		print = ft_strjoin(pad, print);
	}
	free(pad);
	free(tmp);
	return (print);
}

static char			*parse_f_precision(char *print, t_memo *memo)
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
		print[0] == '-' ? i++ : 0;
		buffer = ft_strnew(i);
		while (i > 0)
			buffer[--i] = '0';
		print[0] == '-' ? ft_swap_char(&print[0], &buffer[0]) : 0;
		tmp = print;
		print = ft_strjoin(buffer, print);
		free(tmp);
		free(buffer);
		memo->zero ? memo->zero = 0 : 0;
	}
	return (print);
}

static char			*parse_f_signs(char *print, t_memo *memo)
{
	char			*tmp;

	if (print[0] == '-')
		return (print);
	else if (memo->plus)
	{
		tmp = print;
		print = ft_strjoin("+", print);
		free(tmp);
	}
	else if (memo->space)
	{
		tmp = print;
		print = ft_strjoin(" ", print);
		free(tmp);
	}
	return (print);
}

static char			*parse_f_length(va_list last, t_memo *memo)
{
	char			*pos;
	int				precision;

	if (memo->precision)
		precision = ft_atoi(memo->precision + 1);
	else
		precision = 6;
	if ((pos = ft_strchr(memo->length, 'L')))
		return (ft_ftoa((long double)va_arg(last, long double), precision));
	if ((pos = ft_strchr(memo->length, 'l')))
		return (ft_ftoa((double)va_arg(last, double), precision));
	return (ft_ftoa((double)va_arg(last, double), precision));
}

int					parse_f(va_list last, t_memo *memo)
{
	char			*print;

	print = parse_f_length(last, memo);
	!memo->hash && print[ft_strlen(print) - 1] == '.'
	? print[ft_strlen(print) - 1] = '\0' : 0;
	print = parse_f_precision(print, memo);
	print = parse_f_signs(print, memo);
	print = parse_f_padding(print, memo);
	return (putprint(print, memo->fd));
}
