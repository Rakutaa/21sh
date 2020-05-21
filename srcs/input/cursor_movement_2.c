/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:09:04 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/21 11:09:06 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

static void move_cursor_up(t_terminal *term)
{
        term->in->index = term->in->index - term->size.ws_col;
        if (term->in->index < 0)
            term->in->index = 0;
}

static void move_cursor_down(t_terminal *term)
{
    int     len;

    len = ft_strlen(term->in->string);
    term->in->index = term->in->index + term->size.ws_col;
    if (term->in->index > len)
        term->in->index = len;
}

void		cursor_movement_2(t_terminal *term, int sum)
{
    if (sum == CTRL_UP)
        move_cursor_up(term);
    else if (sum == CTRL_DOWN)
        move_cursor_down(term);
    else if (sum == HOME)
		term->in->index = 0;
	else if (sum == END)
		term->in->index = ft_strlen(term->in->string);
}
