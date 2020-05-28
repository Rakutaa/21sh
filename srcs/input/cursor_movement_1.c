/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:08:56 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/28 13:37:33 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

static void	move_cursor_right(t_terminal *term)
{
	if (term->in->string[term->in->index])
		term->in->index++;
}

static void	move_cursor_left(t_terminal *term)
{
	if (term->in->index > 0)
		term->in->index--;
}

static void	move_cursor_right_word(t_terminal *term)
{
	while (term->in->string[term->in->index] \
	&& term->in->string[term->in->index] == ' ')
		move_cursor_right(term);
	while (term->in->string[term->in->index] \
	&& term->in->string[term->in->index] != ' ')
		move_cursor_right(term);
}

static void	move_cursor_left_word(t_terminal *term)
{
	while (term->in->index > 0 && term->in->string[term->in->index - 1] == ' ')
		move_cursor_left(term);
	while (term->in->index > 0 && term->in->string[term->in->index - 1] != ' ')
		move_cursor_left(term);
}

void		cursor_movement_1(t_terminal *term, int sum)
{
	if (sum == RIGHT)
		move_cursor_right(term);
	else if (sum == LEFT)
		move_cursor_left(term);
	else if (sum == CTRL_RIGHT)
		move_cursor_right_word(term);
	else if (sum == CTRL_LEFT)
		move_cursor_left_word(term);
}
