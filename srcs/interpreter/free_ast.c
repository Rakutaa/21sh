#include "parser_ast.h"

static void	free_ast_node(t_ast_node *ast)
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
	free(list);
}