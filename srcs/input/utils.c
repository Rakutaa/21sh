#include "halfsh.h"

void	display_prompt(void)
{
	write(1, "$>", 2);
}

static void	cursor_position(t_terminal *term)
{
	size_t	cursor;
	size_t	count;

	count = term->in->rows;
	tputs(tgetstr("cr", NULL), 1, print_char);
	while (count--)
		tputs(tgetstr("up", NULL), 1, print_char);
	/* next two rows are used to jump over the prompt. */
	//tputs(tgetstr("nd", NULL), 1, print_char);
	//tputs(tgetstr("nd", NULL), 1, print_char);
	cursor = -1;
	while (++cursor != term->in->index)
	{
		if (cursor / term->size.ws_col && !(cursor % term->size.ws_col))
			tputs(tgetstr("do", NULL), 1, print_char);
		tputs(tgetstr("nd", NULL), 1, print_char);
	}
}

void		print_input(t_terminal *term)
{
	size_t	count;

	term->in->rows = ft_strlen(term->in->string) / term->size.ws_col;
	count = term->in->rows;
	tputs(tgetstr("cr", NULL), 1, print_char);
	tputs(tgetstr("ce", NULL), 1, print_char);
	while (count--)
	{
		tputs(tgetstr("up", NULL), 1, print_char);
		tputs(tgetstr("ce", NULL), 1, print_char);
	}
	//display_prompt();
	ft_putstr(term->in->string);
	cursor_position(term);
}
