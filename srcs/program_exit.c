/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:21 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/28 13:11:23 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

void	program_exit(t_terminal *term, int num)
{
	term ? config_terminal(1, term) : 0;
	num == 1 ? ft_putendl_fd("21sh: Could not allocate memory.", 2) : 0;
	num == 2 ? ft_putendl_fd("21sh: TERM not set.", 2) : 0;
	num == 3 ? \
	ft_putendl_fd("21sh: Could not access the termcap database.", 2) : 0;
	num == 4 ? ft_putendl_fd("21sh: Terminal type is not defined.", 2) : 0;
	if (term)
	{
		ft_lstdel(&term->env, ft_del);
		if (term->in)
		{
			ft_lstdel(&term->in->history, ft_del);
			free(term->in);
		}
		free(term);
	}
	exit(num);
}
