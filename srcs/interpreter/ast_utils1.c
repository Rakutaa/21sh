/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:36:28 by vtran             #+#    #+#             */
/*   Updated: 2020/06/10 18:47:55 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

/*
**this is the substance of syntax grammar. 
**simple cmd.
*/

t_ast_node		*create_factor(char **cmnd, t_redirection_aggregation *list)
{
	t_ast_node	*facto;

	facto = malloc(sizeof(t_ast_node));
	facto->e_node = FACTOR;
	facto->nodes.t_factor.cmds = cmnd;
	facto->nodes.t_factor.list = list;
	return (facto);
}

/*
**this is a pipe between two simple cmd
**left node write to pipe
**right node reads from pipe
*/

t_ast_node		*create_expression(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*express;

	express = malloc(sizeof(t_ast_node));
	express->e_node = EXPR;
	express->nodes.t_expr.left = left;
	express->nodes.t_expr.right = right;
	return (express);
}
