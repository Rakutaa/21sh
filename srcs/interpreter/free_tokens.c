/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 23:04:07 by hege              #+#    #+#             */
/*   Updated: 2020/07/22 23:04:10 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void			free_tokens(t_token *list)
{
	if (list->next)
		free_tokens(list->next);
	free(list->value);
	list->value = NULL;
	free(list);
	list = NULL;
}
