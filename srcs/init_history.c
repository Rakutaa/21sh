/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:21:06 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/22 11:01:56 by vkuokka          ###   ########.fr       */
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

	fd = open(CMD_FILE, O_RDONLY);
	if (fd == -1)
		return ;
	while (get_next_line(fd, &line))
		ft_lstadd(&term->history, ft_lstnew(line, ft_strlen(line)));
	close(fd);
}
