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

void		search_action(t_terminal *term, int sum)
{
	if (sum == LEFT || sum == RIGHT \
	|| sum == CTRL_LEFT || sum == CTRL_RIGHT)
		cursor_movement_1(term, sum);
	else if (sum == CTRL_UP || sum == CTRL_DOWN \
	|| sum == HOME || sum == END)
		cursor_movement_2(term, sum);
	else if (sum == UP || sum == DOWN)
		browse_history(term, sum);
	else if (sum == BACK)
		delete_char(term);
}
