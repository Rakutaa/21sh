/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_clipboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:44:32 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/23 22:49:27 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

/*
** Removes all of the characters after cursor position and
** adds them into internal clipboard.
*/

static void	cut_after(t_terminal *term)
{
	ft_bzero(term->clipboard, ARG_MAX);
	ft_strcat(term->clipboard, term->in->string + term->in->index);
	ft_bzero(term->in->string + term->in->index, \
	ARG_MAX - term->in->index);
	term->in->index = ft_strlen(term->in->string);
}

/*
** Removes all of the characters before cursor position and
** adds them into internal clipboard.
*/

static void	cut_before(t_terminal *term)
{
	ft_bzero(term->clipboard, ARG_MAX);
	ft_strncat(term->clipboard, term->in->string, \
	term->in->index);
	ft_memmove(term->in->string, term->in->string + term->in->index, \
	ARG_MAX - term->in->index);
	term->in->index = 0;
}

/*
** Appends internal cipboard contents into current command.
*/

static void	paste_buffer(t_terminal *term)
{
	size_t	len1;
	size_t	len2;

	if (!term->clipboard[0])
		return ;
	len1 = ft_strlen(term->clipboard);
	len2 = ft_strlen(term->in->string);
	if (len2 + len1 >= ARG_MAX ||
	len2 + term->in->index + len1 >= ARG_MAX)
		return ;
	ft_memmove(term->in->string + term->in->index + len1, \
	term->in->string + term->in->index, \
	len2 + term->in->index);
	ft_memmove(term->in->string + term->in->index, \
	term->clipboard, len1);
	term->in->index += len1;
}

void		shell_clipboard(t_terminal *term, int sum)
{
	if (sum == CTRL_K)
		cut_after(term);
	else if (sum == CTRL_U)
		cut_before(term);
	else if (sum == CTRL_P)
		paste_buffer(term);
}
