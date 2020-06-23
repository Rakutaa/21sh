/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:50:52 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/23 13:31:27 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

/*
** Writes history into a file using recursion.
*/

static void	add_history(int fd, t_list *history)
{
	if (!history)
		return ;
	add_history(fd, history->next);
	ft_putendl_fd(history->content, fd);
}

/*
** Opens file defined in the halfsh.h file and appends current history
** in to the file using add_history function. If the file does not exist,
** Program will create one with appropriate permissions.
*/

void		save_history(t_terminal *term)
{
	int		fd;

	fd = open(CMD_FILE, O_WRONLY|O_CREAT|O_APPEND, 0666);
	if (fd == -1)
		return ;
	add_history(fd, term->history);
	close(fd);
}
