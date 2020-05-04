#include "halfsh.h"
#include "keyboard.h"

static void	navigate_up(t_terminal *term)
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

static void	navigate_down(t_terminal *term)
{
	t_list	*current;
	int	count;

	if (term->h_index <= 0)
		return ;
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

void	history_navigation(t_terminal *term, int sum)
{
	if (sum == UP)
		navigate_up(term);
	else if (sum == DOWN)
		navigate_down(term);
}
