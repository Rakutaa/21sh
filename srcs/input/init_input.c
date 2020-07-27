/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 10:43:42 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/27 14:30:48 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

/*
** Initializes values of the input struct.
*/

void	init_input(t_input *input)
{
	input->sigint = 0;
	input->sigeof = 0;
	ft_memmove(input->prompt, INIT, 4);
	ft_bzero(input->string, ARG_MAX);
	input->index = 0;
	input->line = 0;
}
