#include "halfsh.h"
#include "keyboard.h"

static void	cursor_position(t_terminal *term, size_t len)
{
	size_t	cursor;
	size_t	count;

	count = len / term->size.ws_col;
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

void	print_input(t_terminal *term)
{
	size_t	len;

	len = ft_strlen(term->in->string) + ft_strlen(PROMPT) - 1;
	tputs(tgetstr("rc", NULL), 1, print_char);
	tputs(tgetstr("cd", NULL), 1, print_char);
	ft_putstr(term->in->string);
	cursor_position(term, len);
}
