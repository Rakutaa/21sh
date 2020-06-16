/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:09:43 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/05 15:28:30 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		config_terminal(1, g_term);
		signal(SIGTSTP, SIG_DFL);
		ioctl(1, TIOCSTI, "\x1a");
	}
}

static void	signal_continue(int signum)
{
	if (signum == SIGCONT)
	{
		config_terminal(0, g_term);
		config_signal(g_term);
		ioctl(1, TIOCGWINSZ, &g_term->size);
		print_input(g_term);
		ioctl(1, TIOCSTI, "");
	}
}

static void	signal_kill(int signum)
{
	if (signum)
	{
		g_term->in->index = ft_strlen(g_term->in->string);
		print_input(g_term);
		ft_bzero(g_term->in->string, ft_strlen(g_term->in->string));
		g_term->in->index = 0;
		g_term->in->line = 0;
		write(1, "\n", 1);
		ft_putstr(g_term->in->prompt);
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
