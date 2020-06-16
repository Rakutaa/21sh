/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:34:34 by vtran             #+#    #+#             */
/*   Updated: 2020/06/10 18:52:18 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

/*
**in ast there is this commands fd:s (in, out, err)
**first dup in fd with stdin
**then will put redirections into ast fd:s if some 
**then duplicating output, either pipe or ast->out
**later if this node is the top of the tree and is not expr or if it is 
**expr then if it is not right node of the expr node.
*/

void	helper_dup(t_ast **ast, t_ast_node *obj, int pipe_in)
{
	dup2((*ast)->in, 0);
	visit_factor(obj, ast);
	if ((*ast)->parent->e_node == 1 && obj
	!= (*ast)->parent->nodes.t_expr.right)
		dup2(pipe_in, 1);
	else
		dup2((*ast)->out, 1);
}

/*
**helper to close a file fd, if i need to open a file.
*/

void	helper_close(t_ast_node *obj, t_ast **ast)
{
	t_redirection_aggregation	*node;

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
