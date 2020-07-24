/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:36:28 by vtran             #+#    #+#             */
/*   Updated: 2020/07/24 14:50:17 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

int				is_buildin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd") ||
	!ft_strcmp(str, "setenv") || !ft_strcmp(str, "exit")
	|| !ft_strcmp(str, "unsetenv") || !ft_strcmp(str, "env"))
		return (1);
	return (0);
}

t_ast_n			*create_factor(char **cmnd, t_re_ag *list)
{
	t_ast_n		*facto;

	facto = malloc(sizeof(t_ast_n));
	facto->e_node = FACTOR;
	facto->nodes.t_factor.path_join = NULL;
	if (is_buildin(cmnd[0]))
		facto->nodes.t_factor.e_factor = BUILDIN;
	else
		facto->nodes.t_factor.e_factor = EXEC;
	facto->nodes.t_factor.cmds = cmnd;
	facto->nodes.t_factor.list = list;
	return (facto);
}

t_ast_n			*create_expression(t_ast_n *left, t_ast_n *right)
{
	t_ast_n		*express;

	express = malloc(sizeof(t_ast_n));
	express->e_node = EXPR;
	express->nodes.t_expr.left = left;
	express->nodes.t_expr.right = right;
	return (express);
}
