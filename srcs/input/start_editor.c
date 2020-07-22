/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:00:22 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/22 15:32:16 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

/*
** Adds a character into current command if the length of the command
** does not exceed the limit set by ARG_MAX. If the character is being
** inserted somewhere between current command that already contains character,
** the program shifts bytes from that index to the right once. By doing this
** the character which is being inserted does not overwrite important data.
*/

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

/*
** Gets the ascii value of key pressed from listen_keys function and
** decides if the value will be inserted into the string or does it
** have to search if the value has a specific task to complete. It
** also calls print_input function everytime it loops, which does
** a lot of computing.
*/

static void	loop_editor(t_terminal *term)
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
		if (term->in->sigint)
			init_input(term->in);
		print_input(term);
	}
}

/*
** Acts as a "gateway" into the state where user can type current command.
*/

void		start_editor(t_terminal *term)
{
	char	*line;

	config_terminal(0, term);
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
		print_input(term);
		loop_editor(term);
	}
	config_terminal(1, term);
}
