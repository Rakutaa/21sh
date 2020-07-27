/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:19:08 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/25 00:24:14 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "strings.h"
#include "numbers.h"

static char			*parse_u_padding(char *print, t_memo *memo)
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
		print = ft_strjoin(pad, print);
	free(pad);
	free(tmp);
	return (print);
}

static char			*parse_u_precision(char *print, t_memo *memo)
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
	else if (print[0] == '0')
		print[0] = '\0';
	memo->zero ? memo->zero = 0 : 0;
	return (print);
}

static char			*parse_u_length(va_list last, t_memo *memo)
{
	char			*pos;

	if ((pos = ft_strchr(memo->length, 'h')))
	{
		if (*(pos + 1) == 'h')
			return (ft_itoa_base((unsigned char)
					va_arg(last, unsigned int), 10));
		else
			return (ft_itoa_base((unsigned short int)
					va_arg(last, unsigned int), 10));
	}
	if ((pos = ft_strchr(memo->length, 'l')))
	{
		if (*(pos + 1) == 'l')
			return (ft_itoa_base((unsigned long long)
					va_arg(last, unsigned long long), 10));
		else
			return (ft_itoa_base((unsigned long)
					va_arg(last, unsigned long), 10));
	}
	return (ft_itoa_base((unsigned int)va_arg(last, unsigned int), 10));
}

int					parse_u(va_list last, t_memo *memo)
{
	char			*print;

	print = parse_u_length(last, memo);
	print = parse_u_precision(print, memo);
	print = parse_u_padding(print, memo);
	return (putprint(print, memo->fd));
}
