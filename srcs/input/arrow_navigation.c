#include "halfsh.h"
#include "keyboard.h"

void	navigate_left(t_terminal *term, size_t len, size_t cols)
{
	if (term->in->index > 0)
	{
		if (len / cols && !(len % cols))
		{
			tputs(tgetstr("up", NULL), 1, print_char);
			term->in->line--;
			while (cols--)
				tputs(tgetstr("nd", NULL), 1, print_char);
		}
		else
			tputs(tgetstr("le", NULL), 1, print_char);
		term->in->index--;
	}
}

void	navigate_right(t_terminal *term, size_t len, size_t cols)
{
	if (term->in->string[term->in->index])
	{
		
		if ((len + 1) / cols && !((len + 1) % cols))
		{
			tputs(tgetstr("do", NULL), 1, print_char);
			term->in->line++;
			tputs(tgetstr("cr", NULL), 1, print_char);
		}
		else
			tputs(tgetstr("nd", NULL), 1, print_char);
		term->in->index++;
	}
}

void		arrow_navigation(t_terminal *term, int sum)
{
	size_t	cols;
	size_t	len;

	len = term->in->index + ft_strlen(PROMPT);
	cols = term->size.ws_col;
	if (sum == LEFT)
		navigate_left(term, len, cols);
	else if (sum == RIGHT)
		navigate_right(term, len, cols);
}
