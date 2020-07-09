/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:08:46 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/16 20:29:33 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

/*
** Checks the current history index before searching older entry. If there
** are older entries present the program will update the history index
** and loop through the list until it reaches updated history index. After
** this it will initialize the current command and replace it with contents
** of the list node found.
*/

static void	browse_up(t_terminal *term)
{
	t_list	*current;
	int		count;

	if (term->in->h_index >= (int)ft_lstlen(&term->history) - 1)
		return ;
	term->in->h_index++;
	current = term->history;
	count = 0;
	while (count != term->in->h_index)
	{
		current = current->next;
		count++;
	}
	ft_bzero(term->in->string, ft_strlen(term->in->string));
	ft_memmove(term->in->string, current->content, current->content_size);
	term->in->index = current->content_size;
}

/*
** Behaves the same way as the browse_up function. Current command will
** be initialized to empty string if history has been browsed and
** the history index value is decreased back to zero.
*/

static void	browse_down(t_terminal *term)
{
	t_list	*current;
	int		count;

	if (term->in->h_index < 0)
		return ;
	else if (term->in->h_index == 0)
	{
		ft_bzero(term->in->string, ARG_MAX);
		term->in->index = 0;
		term->in->h_index--;
		return ;
	}
	term->in->h_index--;
	current = term->history;
	count = 0;
	while (count != term->in->h_index)
	{
		current = current->next;
		count++;
	}
	ft_bzero(term->in->string, ft_strlen(term->in->string));
	ft_memmove(term->in->string, current->content, current->content_size);
	term->in->index = current->content_size;
}

void		browse_history(t_terminal *term, int sum)
{
	if (sum == UP)
		browse_up(term);
	else if (sum == DOWN)
		browse_down(term);
}
