/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:00:22 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/21 18:18:28 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

/*
** After being called by loop_editor, This function waits input stream and sums
** up the information received. The sum itself represents ascii value of
** a single keyboard key. The ascii values are defined in keyboard.h header.
*/

static int	listen_keys(void)
{
	char	key[KEY_SIZE + 1];
	ssize_t	bytes;
	size_t	i;
	int		sum;

	bytes = read(1, key, KEY_SIZE);
	key[bytes] = '\0';
	i = -1;
	sum = 0;
	while (key[++i])
		sum += key[i];
	return (sum);
}

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
		if (sum == ENTER)
		{
			tputs(tgetstr("rc", NULL), 1, print_char);
			break ;
		}
		else if (ft_isprint(sum))
			add_char(term, sum);
		else
			search_action(term, sum);
		print_input(term);
	}
}

/*
** Acts as a "gateway" into the state where user can type current command.
*/

void		start_editor(t_terminal *term)
{
	config_terminal(0, term);
	print_input(term);
	loop_editor(term);
	config_terminal(1, term);
}
