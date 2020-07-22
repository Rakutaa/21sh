/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:34:34 by vtran             #+#    #+#             */
/*   Updated: 2020/07/21 14:39:23 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

void		cmd_not_found(char *cmd)
{
	ft_printf("%s: command not found\n", cmd);
}

void	helper_dup(t_ast **ast, t_ast_node *obj, int out)
{
	if ((*ast)->parent->e_node == 1 && 
	obj != (*ast)->parent->nodes.t_expr.right)
	{
		dup2(out, 1);
		close(out);
	}
	visit_factor(obj, ast);
	if ((*ast)->in != 0)
	{
		dup2((*ast)->in, 0);
		close((*ast)->in);
	}
}

void	helper_close(t_ast_node *obj, t_ast **ast)
{
	t_redirection_aggregation	*node;

	if((*ast)->parent->e_node == 1 && (*ast)->in != 0)
	{
		close((*ast)->in);
	}
	node = obj->nodes.t_factor.list;
	while (node)
	{
		if (node && node->e_flag == 0)
		{
			if (node->node.t_redirection.redir[0] == '>' && (*ast)->out != 1)
				close((*ast)->out);
		}
		node = node->next;
	}
}
