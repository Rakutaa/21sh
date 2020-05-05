#include "halfsh.h"
#include "keyboard.h"

static void	delete_char(t_terminal *term)
{
	size_t	len;

	if (term->in->index > 0)
	{
		len = ft_strlen(term->in->string);
		term->in->index--;
		term->in->string[term->in->index] = 0;
		ft_memmove(term->in->string + term->in->index, \
		term->in->string + term->in->index + 1, \
		ft_strlen(term->in->string + term->in->index + 1));
		term->in->string[len - 1] = 0;
	}
}

void		special_keys(t_terminal *term, int sum)
{
	if (sum == LEFT || sum == RIGHT)
		arrow_navigation(term, sum);
	else if (sum == UP || sum == DOWN)
		history_navigation(term, sum);
	else if (sum == CTRL_UP || sum == CTRL_DOWN
		|| sum == CTRL_RIGHT || sum == CTRL_LEFT)
		ctrl_arrow_navigation(term, sum);
	else if (sum == BACK)
		delete_char(term);
	else if (sum == HOME)
		term->in->index = 0;
	else if (sum == END)
		term->in->index = ft_strlen(term->in->string);
}
