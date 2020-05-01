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

static void	cursor_position(t_terminal *term, size_t len)
{
	size_t	cursor;
	size_t	count;

	count = len / term->size.ws_col;
	tputs(tgetstr("cr", NULL), 1, print_char);
	while (count--)
		tputs(tgetstr("up", NULL), 1, print_char);
	cursor = -1;
	while (++cursor != term->in->index + ft_strlen(PROMPT))
	{
		if (cursor / term->size.ws_col && !(cursor % term->size.ws_col))
			tputs(tgetstr("do", NULL), 1, print_char);
		tputs(tgetstr("nd", NULL), 1, print_char);
	}
	if (cursor / term->size.ws_col && !(cursor % term->size.ws_col))
		tputs(tgetstr("do", NULL), 1, print_char);
}

void		print_input(t_terminal *term)
{
	size_t	count;
	size_t	len;

	len = ft_strlen(term->in->string) + ft_strlen(PROMPT) - 1;
	count = term->in->line;
	tputs(tgetstr("cr", NULL), 1, print_char);
	while (count-- && len > term->size.ws_col * count)
		tputs(tgetstr("up", NULL), 1, print_char);
	tputs(tgetstr("cd", NULL), 1, print_char);
	ft_putstr(PROMPT);
	ft_putstr(term->in->string);
	cursor_position(term, len);
	term->in->line = (term->in->index + ft_strlen(PROMPT)) / term->size.ws_col;
}

static void	display_input(t_terminal *term)
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
			special_keys(term, sum);
		print_input(term);
	}
}

void		user_input(t_terminal *term)
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
		display_input(term);
		if (term->in->string[0])
			ft_lstadd(&term->history, ft_lstnew(term->in->string, ft_strlen(term->in->string)));
		// TODO Execution.
		ft_printf("\nInput: %s\n", term->in->string);
	}
}
