/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:09:43 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/10 18:21:41 by vkuokka          ###   ########.fr       */
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
** Configurates terminal and signals into original state before pushing
** suspend signal into device stream.
*/

static void	signal_suspend(int signum)
{
	if (signum == SIGTSTP)
	{
		config_terminal(1, g_term);
		signal(SIGTSTP, SIG_DFL);
		ioctl(1, TIOCSTI, "\x1a");
	}
}

/*
** Configurates terminal and signals back into "shell" mode before
** printing current command and updating cursor position.
*/

static void	signal_continue(int signum)
{
	if (signum == SIGCONT)
	{
		config_terminal(0, g_term);
		config_signal(g_term);
		print_input(g_term);
	}
}

/*
** Clears the current command and prints out a prompt on a empty line.
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
		ft_putchar('\n');
		ft_putstr(g_term->in->prompt);
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
