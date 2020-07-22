/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_ag_dub2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:02:46 by vtran             #+#    #+#             */
/*   Updated: 2020/07/23 00:02:36 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

void		less_greater_than(t_ast **ast, char *file)
{
	(*ast)->rwfd = open(file, O_RDWR | O_APPEND | O_CREAT,
	S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
	dup2((*ast)->rwfd, 0);
	close((*ast)->rwfd);
}
