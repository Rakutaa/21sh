/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:12:01 by hege              #+#    #+#             */
/*   Updated: 2020/07/23 00:38:13 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

static void	free_redir_aggre(t_re_ag *list)
{
	if (list->next)
		free_redir_aggre(list->next);
	if (list->e_flag == AGGRE)
	{
		free(list->node.t_ag.sign);
		if (list->node.t_ag.n)
			free(list->node.t_ag.n);
		if (list->node.t_ag.word)
			free(list->node.t_ag.word);
	}
	else if (list->node.t_re.heredoc)
		free(list->node.t_re.heredoc);
	free(list);
}

static void	free_factor(t_ast_n *factor)
{
	free(factor->nodes.t_factor.cmds);
	if (factor->nodes.t_factor.list)
		free_redir_aggre(factor->nodes.t_factor.list);
	if (factor->nodes.t_factor.path_join)
		free(factor->nodes.t_factor.path_join);
	free(factor);
}

void		free_parser(t_parser_l *list)
{
	if (list->next)
		free_parser(list->next);
	if (list->parser_nodeobj->e_node != TOKEN)
		free_factor(list->parser_nodeobj->nodes.t_a.ast_nodeobj);
	free(list->parser_nodeobj);
	free(list);
}
