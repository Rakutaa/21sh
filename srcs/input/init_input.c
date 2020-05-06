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
			if (ft_strlen(term->in->string) >= ARG_MAX)
				continue ;
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
	!term->in ? program_exit(term, 1) : 0;
	term->in->history = NULL;
	term->in->h_index = -1;
	while (term)
	{
		ft_bzero(term->in->string, ARG_MAX);
		term->in->index = 0;
		ft_putstr(PROMPT);
		tputs(tgetstr("sc", NULL), 1, print_char);
		loop_input(term);
		if (term->in->string[0])
			ft_lstadd(&term->in->history, ft_lstnew(term->in->string, ft_strlen(term->in->string)));
		// TODO Execution.
		// if (ft_strequ(term->in->string, "EXIT"))
		//	return ;
		ft_printf("\nInput: %s\n", term->in->string);
	}
}
