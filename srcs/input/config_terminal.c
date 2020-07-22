/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:04 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/22 17:36:38 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

/*
** Chooses action according to reset value. If reset value
** is positive, It gathers information about the window size
** for term struct and turns off ICANON and ECHO. If it is zero
** the function Configurates the terminal and SIGSTP as they were
** before the program started.
*/

void		config_terminal(int reset, t_terminal *term)
{
	if (reset)
		tcsetattr(STDIN_FILENO, TCSANOW, &term->original);
	else
	{
		if (tcgetattr(STDIN_FILENO, &term->original) == -1)
			program_exit(term, 1);
		term->shell = term->original;
		ioctl(STDIN_FILENO, TIOCGWINSZ, &term->size);
		term->shell.c_lflag &= ~(ICANON | ECHO);
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term->shell) == -1)
			program_exit(term, 1);
		config_signal(term);
	}
}
