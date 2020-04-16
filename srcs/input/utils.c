#include "halfsh.h"

void	display_prompt(void)
{
	write(1, "$>", 2);
}

static void	cursor_position(t_terminal *term)
{
	size_t	cursor;

	tputs(tgetstr("cr", NULL), 1, print_char);
	/* next two rows are used to jump over the prompt. */
	tputs(tgetstr("nd", NULL), 1, print_char);
	tputs(tgetstr("nd", NULL), 1, print_char);
	cursor = -1;
	while (++cursor != term->in->index)
		tputs(tgetstr("nd", NULL), 1, print_char);
}

void		print_input(t_terminal *term)
{
	tputs(tgetstr("cr", NULL), 1, print_char);
	tputs(tgetstr("ce", NULL), 1, print_char);
	display_prompt();
	ft_putstr(term->in->string);
	cursor_position(term);
}
