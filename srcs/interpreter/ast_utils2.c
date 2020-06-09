#include "parser_ast.h"

void		execute_ast(t_ast *ast)
{
	while (ast)
	{
		if (ast->parent->node == factor)
			exec_factor(ast->parent, &ast);
		else
			visit_expression(ast->parent, &ast);
		ast = ast->next;
	}
}

t_ast		*init_ast()
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	ast->in = 0;
	ast->out = 1;
	ast->err = 2;
	ast->parent = NULL;
	ast->next = NULL;
	return ast;
}

//need to check ast token grammar here! esim ;;
//huom. täällä voi olla myös ; ensimmäisenä. jolloin syntax error

t_ast		*create_ast_node(t_ast *ast, t_parser_node_list **list)
{
	if (!ast)
	{
		ast = init_ast();
		ast->parent = (*list)->parser_nodeobj->nodes.ast.ast_nodeobj;
	}
	else
	{
		ast->next = init_ast();
		ast->next->parent = (*list)->next->parser_nodeobj->nodes.ast.ast_nodeobj;
		ast = ast->next;
		*list = (*list)->next;
	}
	*list = (*list)->next;
	return (ast);
}

//ks. onko kaksi pipea peräkkäin 

t_ast_node	*update_ast_parent(t_ast_node *left, t_ast_node *right)
{
	return create_expression(left, right);
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
			tmp->parent = update_ast_parent(tmp->parent, list->next->parser_nodeobj->nodes.ast.ast_nodeobj);
			list = list->next->next;
		}
	}
	return (ast);
}