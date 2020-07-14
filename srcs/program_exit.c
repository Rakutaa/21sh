/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:21 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/13 15:13:02 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

/*
** Returns terminal configuration as it was before launching
** the program. Frees memory allocated in main.c file.
*/

void	program_exit(t_terminal *term, int num)
{
	term ? config_terminal(1, term) : 0;
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
