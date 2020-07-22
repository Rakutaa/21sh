/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:08:22 by hege              #+#    #+#             */
/*   Updated: 2020/07/23 00:15:18 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

static void	free_ast_node(t_ast_n *ast)
{
	if (ast && ast->e_node == EXPR)
	{
		free_ast_node(ast->nodes.t_expr.left);
		free(ast);
	}
}

void		free_ast(t_ast *list)
{
	if (list->next)
		free_ast(list->next);
	free_ast_node(list->parent);
	free(list->pipe);
	free(list->pids);
	free(list);
}
