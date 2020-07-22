/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:34:34 by vtran             #+#    #+#             */
/*   Updated: 2020/07/23 00:16:00 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

void		cmd_not_found(char *cmd)
{
	ft_printf("%s: command not found\n", cmd);
}

void	helper_dup(t_ast **ast, t_ast_n *obj, int out)
{
	if ((*ast)->parent->e_node == 1 && 
	obj != (*ast)->parent->nodes.t_expr.right)
	{
		dup2(out, 1);
		close(out);
	}
	visit_re_ag(obj, ast);
	if ((*ast)->in != 0)
	{
		dup2((*ast)->in, 0);
		close((*ast)->in);
	}
}

void	helper_close(t_ast_n *obj, t_ast **ast)
{
	t_re_ag	*node;

	if((*ast)->parent->e_node == 1 && (*ast)->in != 0)
	{
		close((*ast)->in);
	}
	node = obj->nodes.t_factor.list;
	while (node)
	{
		if (node && node->e_flag == 0)
		{
			if (node->node.t_re.redir[0] == '>' && (*ast)->out != 1)
				close((*ast)->out);
		}
		node = node->next;
	}
}
