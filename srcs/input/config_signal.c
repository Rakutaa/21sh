/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:09:43 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/22 17:42:23 by vkuokka          ###   ########.fr       */
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
		ioctl(STDIN_FILENO, TIOCGWINSZ, &g_term->size);
		ioctl(STDIN_FILENO, TIOCSTI, "");
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
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDIN_FILENO, TIOCSTI, "\x1a");
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
		tputs(tgetstr("ho", NULL), 1, print_char);
		ioctl(STDIN_FILENO, TIOCSTI, "");
	}
}

/*
** Sets sigint flag to 1 and pushes empty string into
** device stream to activate read in listen_keys
*/

static void	signal_kill(int signum)
{
	if (signum)
	{
		g_term->in->sigint = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "");
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
