/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:21 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/23 20:37:18 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "parser_ast.h"

/*
** Saves history before returning terminal configurations as they were
** before entering the program. Frees allocated memory.
*/

void	program_exit(t_terminal *term, int num)
{
	save_history(term);
	term ? config_terminal(1, term) : 0;
	num == 0 ? ft_putendl_fd("21sh: Exit without errors.", STDOUT_FILENO) : 0;
	num == 1 ? ft_putendl_fd("21sh: Exit with errors.", STDERR_FILENO) : 0;
	if (term)
	{
		term->in ? free(term->in) : 0;
		ft_dlstdel(&term->h_head, ft_ddel);
		free_env(term->env);
		free(term);
	}
	exit(num);
}
