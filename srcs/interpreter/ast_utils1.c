#include "parser_ast.h"

t_ast_node		*create_factor(char **cmnd, t_redirection *redirection)
{
	t_ast_node		*facto;
	
	facto = malloc(sizeof(t_ast_node));
	facto->node = factor;
	facto->nodes.factor.cmds = cmnd;
	facto->nodes.factor.redirection = redirection;
	return facto;
}

t_redirection	*create_redirection(char *file, char *sign)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	redir->redir = sign;
	redir->file = file;
	redir->next = NULL;
	return redir;
}

t_ast_node		*create_expression(t_ast_node *left, t_ast_node *right)
{
	t_ast_node *express;

	express = malloc(sizeof(t_ast_node));
	express->node = expr;
	express->nodes.expr.left = left;
	express->nodes.expr.right = right;
	return express;
}

//suljen avatun fd:n exec_factorissa 
//puuttuu myös aggregation.. tää oikeestaan = close fd kait :D

void			visit_factor(t_ast_node *obj, t_ast **ast)
{
	char			*file;
	char			*redir;
	t_redirection	*head;

	head = obj->nodes.factor.redirection;
	while (head)
	{
		file = obj->nodes.factor.redirection->file;
		redir = obj->nodes.factor.redirection->redir;
		if (redir[0] == '>')
			(*ast)->out = open(file, O_WRONLY | O_CREAT | (redir[1] == '\0' ?
			O_TRUNC : O_APPEND), S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
		if (redir[0] == '<')
			(*ast)->in = open(file, O_RDONLY); //make another rule if <<
		head = head->next;
	}
	exec_factor(obj, ast);
}

void			visit_expression(t_ast_node *obj, t_ast **ast)
{
	t_ast_node		*left;
	t_ast_node		*right;

	left = obj->nodes.expr.left;
	right = obj->nodes.expr.right;
	left->node == 0 ? visit_factor(left, ast) : visit_expression(left, ast);
	right->node == 0 ? visit_factor(right, ast) : visit_expression(right, ast);
}