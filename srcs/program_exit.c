/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:21 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/13 13:51:25 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

/*
** Returns terminal into state it was before entering
** the program and exits special modes set by `ti' command.
** Frees the memory allocated in the main.c file.
// UPDATE IF 'te' IS REMOVED
*/

void	program_exit(t_terminal *term, int num)
{
	term ? config_terminal(1, term) : 0;
	//tputs(tgetstr("te", NULL), 1, print_char); //ti is also disabled in main
	num == 0 ? ft_putendl_fd("21sh: Exit without errors.", 1) : 0;
	num == 1 ? ft_putendl_fd("21sh: Exit with errors.", 2) : 0;
	if (term)
	{
		term->in ? free(term->in) : 0;
		ft_dlstdel(&term->h_head, ft_ddel);
		free(term);
	}
	exit(num);
}