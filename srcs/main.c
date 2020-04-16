#include "halfsh.h"

int		main(int argc, char **argv, char **env)
{
	t_terminal *term;

	(void)argc;
	(void)argv;
	term = (t_terminal *)malloc(sizeof(t_terminal));
	if (!term)
		return (1);
	tcgetattr(1, &term->original);
	term->shell = term->original;
	term->env = env;
	config_terminal(0, term);
	config_signal(term);	
	ioctl(1, TIOCGWINSZ, &term->size);
	user_input(term);
	config_terminal(1, term);
	free(term);
	return (0);
}
