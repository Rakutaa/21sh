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
			term->in->string[term->in->index] = sum;
			term->in->index++;
			print_input(term);
		}
		else
			check_other(term, sum);
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
		term->in->rows = 0;
		ft_putstr(PROMPT);
		display_input(term);
		// TODO Execution.
		ft_printf("\nInput: %s\n", term->in->string);
	}
}
