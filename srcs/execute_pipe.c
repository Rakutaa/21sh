/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 11:25:24 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/09 14:42:26 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "lexer.h"
#include "memory.h"

void		execute_pipe(t_terminal *term)
{
	char	*line;

	term->in = (t_input *)malloc(sizeof(t_input));
	!term->in ? program_exit(term, 1) : 0;
	while (get_next_line(0, &line))
	{
		init_input(term->in);
		config_terminal(0, term);
		ft_memmove(term->in->string, line, ARG_MAX);
		free(line);
		config_terminal(1, term);
		init_lexer(term);
	}
}
