/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:13:53 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/08 14:26:59 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "parser_ast.h"

static void execute_editor(t_terminal *term)
{
	char		*editor[3];


	editor[0] = "vim";
	editor[1] = FCFILE;
	editor[2] = NULL;
	execve("/usr/bin/vim", editor, term->enviro);
}

static void	create_file(t_terminal *term, int first, int last)
{
	int		fd;
	t_dlist	*node;
	int		count;

	fd = open(FCFILE, O_WRONLY|O_CREAT, 0666);
	if (fd == -1)
		return ;
	node = term->h_head;
	count = 0;
	while (count != first)
	{
		if (!node->next)
		{
			ft_printf("fc: no such event: %d", first);
			close(fd);
			return ;
		}
		node = node->next;
		count++;
	}
	while(count <= last)
	{
		if (!node)
			break ;
		ft_putendl_fd(node->content, fd);
		node = node->next;
		count++;
	}
	close(fd);
	execute_editor(term);
}

void		fc(t_terminal *term)
{
	create_file(term, 1, 2);
}