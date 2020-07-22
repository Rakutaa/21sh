/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:09:33 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/22 15:18:05 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"
#include "parser_ast.h"

/*
** Deletes character from the command by shifting bytes after the index
** to the left once. The byte after the last character is initialized
** to zero after memmove.
*/

static void	delete_char(t_terminal *term)
{
	size_t	len;

	if (term->in->index > 0)
	{
		len = ft_strlen(term->in->string);
		term->in->index--;
		ft_memmove(term->in->string + term->in->index, \
		term->in->string + term->in->index + 1, \
		ft_strlen(term->in->string + term->in->index + 1));
		term->in->string[len - 1] = 0;
	}
}

static void	eof_action(t_terminal *term)
{
	size_t	len;

	if (!term->in->string[0])
		program_exit(term, 0);
	else if (term->in->string[term->in->index])
	{
		len = ft_strlen(term->in->string);
		ft_memmove(term->in->string + term->in->index, \
		term->in->string + term->in->index + 1, \
		ft_strlen(term->in->string + term->in->index + 1));
		term->in->string[len - 1] = 0;
	}
}

/*
** Chooses right action by comparing sum and different
** definitions from keyboard.h file.
*/

void		search_action(t_terminal *term, int sum)
{
	if (sum == LEFT || sum == RIGHT \
	|| sum == CTRL_LEFT || sum == CTRL_RIGHT)
		cursor_movement_1(term, sum);
	else if (sum == CTRL_UP || sum == CTRL_DOWN \
	|| sum == HOME || sum == END)
		cursor_movement_2(term, sum);
	else if (sum == UP || sum == DOWN \
	|| sum == CTRL_R)
		browse_history(term, sum);
	else if (sum == CTRL_K \
	|| sum == CTRL_U || sum == CTRL_P)
		shell_clipboard(term, sum);
	else if (sum == BACK)
		delete_char(term);
	else if (sum == CTRL_L)
		tputs(tgetstr("ho", NULL), 1, print_char);
	else if (sum == CTRL_D)
		eof_action(term);
}
