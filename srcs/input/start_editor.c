/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:00:22 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/27 14:46:25 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

static void	add_char(t_terminal *term, int sum)
{
	if (ft_strlen(term->in->string) >= ARG_MAX)
		return ;
	if (term->in->string[term->in->index])
		ft_memmove(term->in->string + term->in->index + 1, \
		term->in->string + term->in->index, \
		ft_strlen(term->in->string + term->in->index));
	term->in->string[term->in->index] = sum;
	term->in->index++;
}

static void	editor_loop(t_terminal *term)
{
	int		sum;

	while (term)
	{
		sum = listen_keys();
		if (sum == ENTER || term->in->sigint)
		{
			tputs(tgetstr("rc", NULL), 1, print_char);
			break ;
		}
		else if (ft_isprint(sum))
			add_char(term, sum);
		else
			search_action(term, sum);
		if (term->in->sigeof)
			break ;
		print_input(term);
	}
}

/*
** Chooses between reading line from file and showing line editor.
*/

void		start_editor(t_terminal *term)
{
	char	*line;

	if (!isatty(STDIN_FILENO))
	{
		if (!get_next_line(0, &line))
			program_exit(term, 0);
		if (ft_strlen(line) > ARG_MAX)
			program_exit(term, 1);
		ft_strcat(term->in->string, line);
		free(line);
	}
	else
	{
		config_terminal(0, term);
		print_input(term);
		editor_loop(term);
		config_terminal(1, term);
	}
}
