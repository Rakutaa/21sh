/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:09:26 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/17 13:30:14 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

/*
** Moves cursor to the beginning of the line where prompt is located.
** After this the function moves cursor one by one until the position
** matches term->in->index. May not be the most effective way, but it works.
*/

static void		cursor_position(t_terminal *term, size_t len)
{
	size_t	cursor;
	size_t	count;

	count = len / term->size.ws_col;
	tputs(tgetstr("cr", NULL), 1, print_char);
	while (count--)
		tputs(tgetstr("up", NULL), 1, print_char);
	cursor = -1;
	while (++cursor != term->in->index + ft_strlen(term->in->prompt))
	{
		if (cursor / term->size.ws_col && !(cursor % term->size.ws_col))
			tputs(tgetstr("do", NULL), 1, print_char);
		tputs(tgetstr("nd", NULL), 1, print_char);
	}
	if (cursor / term->size.ws_col && !(cursor % term->size.ws_col))
		tputs(tgetstr("do", NULL), 1, print_char);
}

/*
** Moves cursor to the beginning of the line where prompt is located.
** After this the function prints out prompt and current command overwriting
** older text in the same process. Uses termcaps `sc' command to save cursor
** location before calling cursor_position function. Amount of lines used in
** printing is saved to the term->in->line variable.
*/

void			print_input(t_terminal *term)
{
	size_t		count;
	size_t		len;

	len = ft_strlen(term->in->string) + ft_strlen(term->in->prompt) - 1;
	count = term->in->line;
	tputs(tgetstr("cr", NULL), 1, print_char);
	while (count-- && len > term->size.ws_col * count)
		tputs(tgetstr("up", NULL), 1, print_char);
	tputs(tgetstr("cd", NULL), 1, print_char);
	ft_putstr(term->in->prompt);
	ft_putstr(term->in->string);
	tputs(tgetstr("sc", NULL), 1, print_char);
	cursor_position(term, len);
	term->in->line = (term->in->index + ft_strlen(term->in->prompt)) \
	/ term->size.ws_col;
}
