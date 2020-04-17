#include "halfsh.h"

static void	cursor_position(t_terminal *term)
{
	size_t	cursor;
	size_t	count;

	count = term->in->rows;
	tputs(tgetstr("cr", NULL), 1, print_char);
	while (count--)
		tputs(tgetstr("up", NULL), 1, print_char);
	cursor = -1;
	while (++cursor != term->in->index + ft_strlen(PROMPT))
	{
		if (cursor / term->size.ws_col && !(cursor % term->size.ws_col))
			tputs(tgetstr("do", NULL), 1, print_char);
		tputs(tgetstr("nd", NULL), 1, print_char);
	}
	if (cursor / term->size.ws_col && !(cursor % term->size.ws_col))
		tputs(tgetstr("do", NULL), 1, print_char);
}

void		print_input(t_terminal *term)
{
	size_t	count;
	size_t	len;

	len = ft_strlen(term->in->string) + ft_strlen(PROMPT) - 1;
	term->in->rows = len / term->size.ws_col;
	count = term->in->rows;
	tputs(tgetstr("cr", NULL), 1, print_char);
	while (count-- && len > term->size.ws_col * count)
		tputs(tgetstr("up", NULL), 1, print_char);
	tputs(tgetstr("cd", NULL), 1, print_char);
	ft_putstr(PROMPT);
	ft_putstr(term->in->string);
	cursor_position(term);
}
