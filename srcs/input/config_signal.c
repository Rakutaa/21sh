/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:09:43 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/17 13:26:40 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

static t_terminal *g_term;

/*
** Updates term struct information about the window size and pushes
** empty string into device stream to activate read in listen_keys.
*/

static void	signal_resize(int signum)
{
	if (signum == SIGWINCH)
	{
		ioctl(1, TIOCGWINSZ, &g_term->size);
		ioctl(1, TIOCSTI, "");
	}
}

/*
** Configurates terminal into original state before pushing
** suspend signal into device stream.
*/

static void	signal_suspend(int signum)
{
	if (signum == SIGTSTP)
	{
		config_terminal(1, g_term);
		tputs(tgetstr("te", NULL), 1, print_char);
		signal(SIGTSTP, SIG_DFL);
		ioctl(1, TIOCSTI, "\x1a");
	}
}

/*
** Configurates terminal back into "shell" mode before pushing
** empty string into device stream to activate read in listen_keys.
*/

static void	signal_continue(int signum)
{
	if (signum == SIGCONT)
	{
		config_terminal(0, g_term);
		tputs(tgetstr("ti", NULL), 1, print_char);
		tputs(tgetstr("ho", NULL), 1, print_char);
		ioctl(1, TIOCSTI, "");
	}
}

/*
** Clears the current command and prints out a prompt on a empty line.
** Takes advantage of restoring cursor position saved by `sc' in
** print_input function by using termcaps `rc' command.
*/

static void	signal_kill(int signum)
{
	if (signum)
	{
		g_term->in->index = ft_strlen(g_term->in->string);
		print_input(g_term);
		ft_bzero(g_term->in->string, ft_strlen(g_term->in->string));
		g_term->in->index = 0;
		g_term->in->line = 0;
		tputs(tgetstr("rc", NULL), 1, print_char);
		ft_putchar('\n');
		ft_putstr(g_term->in->prompt);
		tputs(tgetstr("sc", NULL), 1, print_char);
	}
}

/*
** Goes through the available signals and sets them into "shell" mode.
** Global variable is used because the second parameter of the signal
** function has to take only one parameter.
*/

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
