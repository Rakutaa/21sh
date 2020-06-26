/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:08:46 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/26 14:09:33 by vkuokka          ###   ########.fr       */
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
	if (term->h_current)
	{
		ft_bzero(term->in->string, ft_strlen(term->in->string));
		ft_memmove(term->in->string, term->h_current->content, \
		term->h_current->content_size);
		term->in->index = term->h_current->content_size;
		if (term->h_current->next)
			term->h_current = term->h_current->next;
	}
}

/*
** Moves history to newer entry and replaces current
** command with the contents of that history node.
*/

static void	browse_down(t_terminal *term)
{
	if (term->h_current)
	{
		if (!term->h_current->prev)
		{
			ft_bzero(term->in->string, ft_strlen(term->in->string));
			term->in->index = 0;
			return ;
		}
		term->h_current = term->h_current->prev;
		ft_bzero(term->in->string, ft_strlen(term->in->string));
		ft_memmove(term->in->string, term->h_current->content, \
		term->h_current->content_size);
		term->in->index = term->h_current->content_size;
	}
}

void		browse_history(t_terminal *term, int sum)
{
	if (sum == UP)
		browse_up(term);
	else if (sum == DOWN)
		browse_down(term);
}
