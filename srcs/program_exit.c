/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:21 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/23 14:35:36 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "parser_ast.h"

/*
** Returns terminal configuration as it was before launching
** the program. Frees allocated memory.
*/

void	program_exit(t_terminal *term, int num)
{
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
