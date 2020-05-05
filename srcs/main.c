#include "halfsh.h"

int		main(int argc, char **argv, char **env)
{
	t_terminal *term;

	(void)argc;
	(void)argv;
	term = (t_terminal *)malloc(sizeof(t_terminal));
	!term ? program_exit(term, 1) : 0;
	tcgetattr(1, &term->original);
	term->shell = term->original;
	ioctl(1, TIOCGWINSZ, &term->size);
	term->env = env;
	term->in = NULL;
	config_terminal(0, term);
	config_signal(term);
	init_input(term);
	config_terminal(1, term);
	program_exit(term, 0);
}
