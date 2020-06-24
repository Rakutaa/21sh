/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:21:06 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/24 09:51:56 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "get_next_line.h"

/*
** Opens file defined in halfsh.h file and adds every line of that file into
** history linked list.
*/

void		init_history(t_terminal *term)
{
	int		fd;
	char	*line;
	t_list	*node;

	fd = open(CMD_FILE, O_RDONLY);
	if (fd == -1)
		return ;
	while (get_next_line(fd, &line))
	{
		node = ft_lstnew(NULL, 0);
		node->content = line;
		node->content_size = ft_strlen(line);
		!term->history ? term->history = node :
		ft_lstaddback(&term->history, node);
	}
	close(fd);
}
