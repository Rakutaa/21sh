/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:04 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/28 13:12:29 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

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
		term->shell.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(1, TCSAFLUSH, &term->shell);
	}
	else if (success < 0)
		program_exit(term, 3);
	else if (success == 0)
		program_exit(term, 4);
}

static void	init_original(struct termios original)
{
	tputs(tgetstr("te", NULL), 1, print_char);
	tcsetattr(1, TCSAFLUSH, &original);
}

void		config_terminal(int reset, t_terminal *term)
{
	if (reset)
		init_original(term->original);
	else
		init_shell(term);
}
