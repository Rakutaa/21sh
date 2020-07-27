/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:41:51 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/25 00:36:53 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <stdbool.h>

# define SPECIFIERS "cspdiouxXf"
# define FWPL "#0-+ 123456789.*hlL"
# define FLAGS "#0-+ "
# define WIDTH "0123456789*"
# define PRECISION ".0123456789*"
# define LENGTH "hlL"

typedef struct		s_memo
{
	bool			hash;
	bool			zero;
	bool			minus;
	bool			plus;
	bool			space;
	char			*width;
	char			*precision;
	char			*length;
	int				fd;
}					t_memo;

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
const char			*parse(int fd, const char *format, va_list last, int *p);
int					parse_c(int c, t_memo *memo);
int					parse_s(va_list last, t_memo *memo);
int					parse_p(va_list last, t_memo *memo);
int					parse_di(va_list last, t_memo *memo);
int					parse_i(va_list last, t_memo *memo);
int					parse_o(va_list last, t_memo *memo);
int					parse_u(va_list last, t_memo *memo);
int					parse_lower_x(va_list last, t_memo *memo);
int					parse_upper_x(va_list last, t_memo *memo);
int					parse_f(va_list last, t_memo *memo);
int					putprint(char *print, int fd);

#endif
