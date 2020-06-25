/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:08:46 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/24 23:32:36 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

/*
** Moves history to older entry and replaces current
** command with the contents of that history node.
*/

static void	browse_up(t_terminal *term)
{
	if (term->history && term->history->next)
	{
		term->history = term->history->next;
		ft_bzero(term->in->string, ft_strlen(term->in->string));
		ft_memmove(term->in->string, term->history->content, \
		term->history->content_size);
		term->in->index = term->history->content_size;
	}
}

/*
** Moves history to newer entry and replaces current
** command with the contents of that history node.
*/

static void	browse_down(t_terminal *term)
{
	if (term->history && term->history->prev)
	{
		term->history = term->history->prev;
		ft_bzero(term->in->string, ft_strlen(term->in->string));
		ft_memmove(term->in->string, term->history->content, \
		term->history->content_size);
		term->in->index = term->history->content_size;
	}
}

void		browse_history(t_terminal *term, int sum)
{
	if (sum == UP)
		browse_up(term);
	else if (sum == DOWN)
		browse_down(term);
}
