/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:50:52 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/22 15:43:40 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

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
