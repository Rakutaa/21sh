/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:21 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/16 12:18:17 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "parser_ast.h"

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
		free_env(term->env);
		term->in ? free(term->in) : 0;
		ft_lstdel(&term->history, ft_del);
		free(term);
	}
	exit(num);
}
