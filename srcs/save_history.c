/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:50:52 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/24 23:23:39 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

/*
** Opens file defined in the halfsh.h file and appends current history
** in to the file using add_history function. If the file does not exist,
** Program will create one with appropriate permissions.
// POSSIBLE ISSUES WITH STRING LENGTH!
*/

void		save_history(t_terminal *term)
{
	int		fd;
	t_dlist	*current;
	int		count;

	fd = open(H_FILE, O_WRONLY|O_CREAT, 0666);
	if (fd == -1)
		return ;
	current = term->history;
	count = 0;
	while (count < H_LEN && current)
	{
		ft_putendl_fd(current->content, fd);
		current = current->next;
		count++;
	}
	close(fd);
}
