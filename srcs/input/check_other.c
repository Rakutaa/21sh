#include "halfsh.h"
#include "keyboard.h"

void		check_other(t_terminal *term, int sum)
{
	size_t	len;

	if (sum == BACK && term->in->index > 0)
	{
		len = ft_strlen(term->in->string);
		tputs(tgetstr("le", NULL), 1, print_char);
		tputs(tgetstr("ce", NULL), 1, print_char);
		term->in->index--;
		term->in->string[term->in->index] = 0;
		ft_memmove(term->in->string + term->in->index, \
		term->in->string + term->in->index + 1, \
		ft_strlen(term->in->string + term->in->index + 1));
		term->in->string[len - 1] = 0;
		print_input(term);
	}
	else if (sum == LEFT || sum == RIGHT)
		arrow_navigation(term, sum);
}
