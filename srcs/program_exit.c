/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:21 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/15 16:51:38 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

/*
** Returns terminal into state it was before entering
** the program and exits special modes set by `ti' command.
** Frees the memory allocated in the main.c file.
*/

void	program_exit(t_terminal *term, int num)
{
	term ? config_terminal(1, term) : 0;
	tputs(tgetstr("te", NULL), 1, print_char);
	num == 0 ? ft_putendl_fd("21sh: Exit without errors.", 1) : 0;
	num == 1 ? ft_putendl_fd("21sh: Exit with errors.", 2) : 0;
	if (term)
	{
		ft_lstdel(&term->env, ft_del);
		if (term->in)
		{
			ft_lstdel(&term->in->history, ft_del);
			free(term->in);
		}
		free(term);
	}
	exit(num);
}
