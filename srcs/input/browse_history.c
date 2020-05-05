#include "halfsh.h"
#include "keyboard.h"

static void	browse_up(t_terminal *term)
{
	t_list	*current;
	int	count;

	if (term->h_index >= (int)ft_lstlen(&term->history) - 1)
		return ;
	term->h_index++;
	current = term->history;
	count = 0;
	while (count != term->h_index)
	{
		if (!current->next)
			return ;
		current = current->next;
		count++;
	}
	ft_bzero(term->in->string, ft_strlen(term->in->string));
	ft_memmove(term->in->string, current->content, current->content_size);
	term->in->index = current->content_size;
}

static void	browse_down(t_terminal *term)
{
	t_list	*current;
	int		count;

	if (term->h_index < 0)
		return ;
	else if (term->h_index == 0)
	{
		ft_bzero(term->in->string, ARG_MAX);
		term->in->index = 0;
		term->h_index--;
		return ;
	}
	term->h_index--;
	current = term->history;
	count = 0;
	while (count != term->h_index)
	{
		if (!current->next)
			return ;
		current = current->next;
		count++;
	}
	ft_bzero(term->in->string, ft_strlen(term->in->string));
	ft_memmove(term->in->string, current->content, current->content_size);
	term->in->index = current->content_size;
}

void	browse_history(t_terminal *term, int sum)
{
	if (sum == UP)
		browse_up(term);
	else if (sum == DOWN)
		browse_down(term);
}
