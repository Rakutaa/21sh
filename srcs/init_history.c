/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:21:06 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/08 13:04:15 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "get_next_line.h"

/*
** Opens file defined in halfsh.h file and adds every line of that file into
** the history linked list.
*/

void		init_history(t_terminal *term)
{
	int		fd;
	char	*line;
	t_dlist	*node;
	int		count;

	fd = open(HISTFILE, O_RDONLY);
	if (fd == -1)
		return ;
	node = NULL;
	count = 0;
	while (count < HISTSIZE && get_next_line(fd, &line))
	{
		node = ft_dlstnew(NULL, 0);
		if (!node)
			break ;
		node->content = line;
		node->content_size = ft_strlen(line) + 1;
		ft_dlstaddback(&term->h_head, node);
		count++;
	}
	term->h_tail = node;
	close(fd);
}
