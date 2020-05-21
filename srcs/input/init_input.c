/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:00:22 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/21 11:09:11 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

static int	listen_keys(void)
{
	char	key[KEY_SIZE + 1];
	ssize_t	bytes;
	size_t	i;
	int	sum;

	bytes = read(1, key, KEY_SIZE);
	key[bytes] = '\0';
	i = -1;
	sum = 0;
	while (key[++i])
		sum += key[i];
	return (sum);
}

static void	loop_input(t_terminal *term)
{
	int	sum;

	while (term)
	{
		sum = listen_keys();
		if (sum == ENTER)
			return ;
		if (ft_isprint(sum))
		{
			if (ft_strlen(term->in->string) >= ARG_MAX)
				continue ;
			if (term->in->string[term->in->index])	
				ft_memmove(term->in->string + term->in->index + 1, \
				term->in->string + term->in->index, \
				ft_strlen(term->in->string + term->in->index));
			term->in->string[term->in->index] = sum;
			term->in->index++;
		}
		else
			search_action(term, sum);
		print_input(term);
	}
}

void		init_input(t_terminal *term)
{
	tputs(tgetstr("sc", NULL), 1, print_char);
	print_input(term);
	loop_input(term);
}
