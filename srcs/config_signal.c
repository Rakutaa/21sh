#include "halfsh.h"

static t_terminal *g_term;

static void	signal_resize(int signum)
{
	if (signum == SIGWINCH)
	{
		ioctl(1, TIOCGWINSZ, &g_term->size);
		ioctl(1, TIOCSTI, "");
	}
}

static void	signal_suspend(int signum)
{
	if (signum == SIGTSTP)
	{
		signal(SIGTSTP, SIG_DFL);
		config_terminal(1, g_term);
		ioctl(1, TIOCSTI, "\x1a");
	}
}

static void	signal_continue(int signum)
{
	if (signum == SIGCONT)
	{
		config_terminal(0, g_term);
		tputs(tgetstr("rc", NULL), 1, print_char);
		tputs(tgetstr("cr", NULL), 1, print_char);
		ft_putstr(PROMPT);
		print_input(g_term);
		ioctl(1, TIOCSTI, "");
	}
}

static void	signal_kill(int signum)
{
	if (signum)
	{
		ft_bzero(g_term->in->string, ft_strlen(g_term->in->string));
		g_term->in->index = 0;
		write(1, "\n", 1);
		ft_putstr(PROMPT);
		tputs(tgetstr("sc", NULL), 1, print_char);
	}
}

void		config_signal(t_terminal *term)
{
	g_term = term;
	signal(SIGWINCH, signal_resize);
	signal(SIGTSTP, signal_suspend);
	signal(SIGCONT, signal_continue);
	signal(SIGINT, signal_kill);
	signal(SIGSTOP, signal_kill);
	signal(SIGKILL, signal_kill);
	signal(SIGQUIT, signal_kill);
	signal(SIGABRT, signal_kill);
}
