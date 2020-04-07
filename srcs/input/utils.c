#include "halfsh.h"

static void	cursor_position(t_input *in)
{
	size_t	cursor;

	tputs(tgetstr("cr", NULL), 1, print_char);
	tputs(tgetstr("nd", NULL), 1, print_char);
	tputs(tgetstr("nd", NULL), 1, print_char);
	cursor = -1;
	while (++cursor != in->index)
		tputs(tgetstr("nd", NULL), 1, print_char);
}

void		print_section(t_input *in)
{
	tputs(tgetstr("cr", NULL), 1, print_char);
	tputs(tgetstr("nd", NULL), 1, print_char);
	tputs(tgetstr("nd", NULL), 1, print_char);
	tputs(tgetstr("ce", NULL), 1, print_char);
	ft_putstr(in->string);
	cursor_position(in);
}
