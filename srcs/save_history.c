/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:50:52 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/09 14:43:18 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

/*
** Opens file defined in the halfsh.h file and appends current history
** in to the file using add_history function. If the file does not exist,
** Program will create one with appropriate permissions.
*/

void		save_history(t_terminal *term)
{
	int		fd;
	t_dlist	*current;
	int		count;

	fd = open(HISTFILE, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
		return ;
	current = term->h_head;
	count = 0;
	while (count < HISTSIZE && current)
	{
		ft_putendl_fd(current->content, fd);
		current = current->next;
		count++;
	}
	close(fd);
}
