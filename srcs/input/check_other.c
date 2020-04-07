#include "halfsh.h"
#include "keyboard.h"

static void	check_arrows(t_terminal *term, int sum)
{
	if (sum == LEFT && term->in->index > 0)
	{
		tputs(tgetstr("le", NULL), 1, print_char);
		term->in->index--;
	}
	else if (sum == RIGHT && term->in->string[term->in->index])
	{
		tputs(tgetstr("nd", NULL), 1, print_char);
		term->in->index++;
	}
}

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
		print_section(term->in);
	}
	else
		check_arrows(term, sum);
}
