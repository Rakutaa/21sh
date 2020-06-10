/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:04 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/10 17:33:42 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

/*
** Configurates termcaps, puts the terminal into whatever special
** modes are needed or appropriate for programs that move the cursor
** nonsequentially around the screen and moves the cursor to
** the upper left corner of the screen. Also gathers information about
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
		tputs(tgetstr("ti", NULL), 1, print_char);
		tputs(tgetstr("ho", NULL), 1, print_char);
		ioctl(1, TIOCGWINSZ, &term->size);
		term->shell.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(1, TCSAFLUSH, &term->shell);
	}
	else if (success < 0)
		program_exit(term, 3);
	else if (success == 0)
		program_exit(term, 4);
}

/*
** Simply undoes what is done by the termcap `ti' string and
** sets the terminal config as it was when program started.
*/

static void	init_original(struct termios original)
{
	tputs(tgetstr("te", NULL), 1, print_char);
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
