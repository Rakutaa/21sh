/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:19:01 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/25 00:32:32 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "strings.h"
#include "numbers.h"

static char			*parse_s_padding(char *print, t_memo *memo)
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

static char			*parse_s_precision(char *print, t_memo *memo)
{
	size_t			i;

	if (!memo->precision)
		return (print);
	i = ft_atoi(memo->precision + 1);
	if (i > ft_strlen(print))
		return (print);
	print[i] = '\0';
	return (print);
}

int					parse_s(va_list last, t_memo *memo)
{
	char			*print;

	print = (char *)va_arg(last, char *);
	if (!print)
		print = ft_strdup("(null)");
	else
		print = ft_strdup(print);
	print = parse_s_precision(print, memo);
	print = parse_s_padding(print, memo);
	return (putprint(print, memo->fd));
}
