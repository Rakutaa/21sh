/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 10:43:42 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/17 13:26:43 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

/*
** Initializes values of the input struct.
*/

void	init_input(t_input *input)
{
	input->h_index = -1;
	ft_memmove(input->prompt, INIT, 3);
	ft_bzero(input->string, ARG_MAX);
	input->index = 0;
	input->line = 0;
}
