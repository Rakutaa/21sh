#include "halfsh.h"

static int	init_shell(struct termios shell)
{
	char	*type;
	char	buffer[2048];
	int		success;

	type = getenv("TERM");
	if (!type)
	{
		ft_fprintf(2, "ft_select: TERM not set\n");
		return (1);
	}
	success = tgetent(buffer, type);
	if (success > 0)
	{
		tputs(tgetstr("ti", NULL), 1, print_char);
		tputs(tgetstr("ho", NULL), 1, print_char);
		shell.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(1, TCSAFLUSH, &shell);
		return (0);
	}
	else if (success < 0)
		ft_fprintf(2, "ft_select: Could not access the termcap database\n");
	else if (success == 0)
		ft_fprintf(2, "ft_select: Terminal type %s is not defined\n", type);
	return (1);
}

static void	init_original(struct termios original)
{
	tputs(tgetstr("te", NULL), 1, print_char);
	tcsetattr(1, TCSAFLUSH, &original);
}

int			config_terminal(int reset, t_terminal *term)
{
	if (reset)
		init_original(term->original);
	else if (init_shell(term->shell))
		return (1);
	return (0);
}
