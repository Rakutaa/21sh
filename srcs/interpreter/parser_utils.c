/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:48:58 by vtran             #+#    #+#             */
/*   Updated: 2020/07/23 00:14:37 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser_ast.h"

static t_parser_l	*init_parser_l(void)
{
	t_parser_l	*list;

	list = malloc(sizeof(t_parser_l));
	list->parser_nodeobj = NULL;
	list->next = NULL;
	return (list);
}

void						add_node_to_parser_node_list(
t_parser_l **list, t_parser_n *ast_nodeobj,
t_parser_n *token_nodeobj)
{
	t_parser_l	*tmp;

	if (!*list)
	{
		(*list) = init_parser_l();
		(*list)->parser_nodeobj = ast_nodeobj;
		tmp = (*list);
	}
	else
	{
		tmp = (*list);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_parser_l();
		tmp->next->parser_nodeobj = ast_nodeobj;
		tmp = tmp->next;
	}
	if (token_nodeobj)
	{
		tmp->next = init_parser_l();
		tmp->next->parser_nodeobj = token_nodeobj;
	}
}
