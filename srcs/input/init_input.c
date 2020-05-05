#include "halfsh.h"
#include "keyboard.h"

static int	listen_keys(void)
{
	char	key[KEY_SIZE + 1];
	ssize_t	bytes;
	size_t	i;
	int	sum;

	bytes = read(1, key, KEY_SIZE);
	key[bytes] = '\0';
	i = -1;
	sum = 0;
	while (key[++i])
		sum += key[i];
	return (sum);
}

static void	loop_input(t_terminal *term)
{
	int	sum;

	while (term)
	{
		sum = listen_keys();
		if (sum == ENTER)
			return ;
		if (ft_isprint(sum))
		{
			if (term->in->string[term->in->index])		
				ft_memmove(term->in->string + term->in->index + 1, \
				term->in->string + term->in->index, \
				ft_strlen(term->in->string + term->in->index));
			term->in->string[term->in->index] = sum;
			term->in->index++;
		}
		else
			search_action(term, sum);
		print_input(term);
	}
}

void		init_input(t_terminal *term)
{
	term->in = (t_input *)malloc(sizeof(t_input));

	if (!term->in)
		return ;
	while (term)
	{
		ft_bzero(term->in->string, ARG_MAX);
		term->in->index = 0;
		term->in->line = 0;
		term->h_index = -1;
		ft_putstr(PROMPT);
		loop_input(term);
		if (term->in->string[0])
			ft_lstadd(&term->history, ft_lstnew(term->in->string, ft_strlen(term->in->string)));
		// TODO Execution.
		ft_printf("\nInput: %s\n", term->in->string);
	}
}
