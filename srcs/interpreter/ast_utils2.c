/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:39:26 by vtran             #+#    #+#             */
/*   Updated: 2020/06/10 19:12:56 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

/*
**logic was to make as many AST as there is cmds. 
**cmds was separated by ;
**if node is factor, will just exec. 
**else opens the tree recursively
**and the return from recursion will start
**when this parent node is Factor. 
*/

void		execute_ast(t_ast *ast)
{
	while (ast)
	{
		if (ast->parent->e_node == FACTOR)
			exec_factor(ast->parent, &ast);
		else
			visit_expression(ast->parent, &ast);
		ast = ast->next;
	}
}

t_ast		*init_ast(void)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	ast->in = 0;
	ast->out = 1;
	ast->err = 2;
	ast->parent = NULL;
	ast->next = NULL;
	return (ast);
}

/*
**either there is mulple cmds separated ; or first cmd
*/

t_ast		*create_ast_node(t_ast *ast, t_parser_node_list **list)
{
	if (!ast)
	{
		ast = init_ast();
		ast->parent = (*list)->parser_nodeobj->nodes.ast.ast_nodeobj;
	}
	else if ((*list)->next) //tässä!!!!! HEUREKA!!
	// else
	{
		ast->next = init_ast();
		ast->next->parent =
		(*list)->next->parser_nodeobj->nodes.ast.ast_nodeobj;
		ast = ast->next;
		*list = (*list)->next;
	}
	*list = (*list)->next;
	return (ast);
}

/*
**ast->parent update. meaning that there is atleast one pipe
*/

t_ast_node	*update_ast_parent(t_ast_node *left, t_ast_node *right)
{
	return (create_expression(left, right));
}

t_ast		*create_ast_list(t_parser_node_list *list)
{
	t_ast	*ast;
	t_ast	*tmp;

	ast = NULL;
	tmp = ast;
	while (list)
	{
		if (list->parser_nodeobj->nodes.token.e_type != TOKEN_P)
		{
			tmp = create_ast_node(tmp, &list);
			if (!ast)
				ast = tmp;
		}
		else
		{
			tmp->parent = update_ast_parent(tmp->parent,
			list->next->parser_nodeobj->nodes.ast.ast_nodeobj);
			list = list->next->next;
		}
	}
	return (ast);
}
