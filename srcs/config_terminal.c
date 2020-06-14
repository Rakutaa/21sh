/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:04 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/14 13:49:21 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

/*
** Configurates termcaps. Also gathers information about
** the window size for term struct and turns off ICANON and ECHO.
*/

static void	init_shell(t_terminal *term)
{
	char	*type;
	char	buffer[2048];
	int		success;

	type = getenv("TERM");
	!type ? program_exit(term, 2) : 0;
	success = tgetent(buffer, type);
	if (success > 0)
	{
		ioctl(1, TIOCGWINSZ, &term->size);
		term->shell.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(1, TCSAFLUSH, &term->shell);
		config_signal(term);
	}
	else if (success < 0)
		program_exit(term, 3);
	else if (success == 0)
		program_exit(term, 4);
}

/*
** Configurates the terminal and SIGSTP as they were
** before the program started.
*/

static void	init_original(struct termios original)
{
	signal(SIGTSTP, SIG_DFL);
	tcsetattr(1, TCSAFLUSH, &original);
}

/*
** Chooses action according to reset value.
*/

void		config_terminal(int reset, t_terminal *term)
{
	if (reset)
		init_original(term->original);
	else
		init_shell(term);
}
