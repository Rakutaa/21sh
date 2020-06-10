#include "parser_ast.h"

t_ast_node		*create_factor(char **cmnd, t_redirection_aggregation *list)
{
	t_ast_node		*facto;
	
	facto = malloc(sizeof(t_ast_node));
	facto->node = factor;
	facto->nodes.factor.cmds = cmnd;
	facto->nodes.factor.list = list;
	return facto;
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

//lisää tämä tonne helper_duppiin.. 
//syy tähän on tuossa aggregation hommellissa..
//suljen avatun fd:n exec_factorissa 
//puuttuu myös aggregation.. tää oikeestaan = close fd kait :D

void			visit_factor(t_ast_node *obj, t_ast **ast)
{
	char						*file;
	char						*redir;
	t_redirection_aggregation	*head;

	head = obj->nodes.factor.list;
	while (head)
	{
		if (head->flag == 0)
		{
			file = head->token.redirection.file;
			redir = head->token.redirection.redir;
			if (redir[0] == '>')
			{
				close((*ast)->out);
				(*ast)->out = open(file, O_WRONLY | O_CREAT | (redir[1] == '\0' ?
				O_TRUNC : O_APPEND), S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
			}
			if (redir[0] == '<')
			{
				close((*ast)->in);
				(*ast)->in = open(file, O_RDONLY, O_CLOEXEC); //make another rule if <<
				dup2((*ast)->in, 0);
			}
		}
		else if (head->flag == 1)
		{
			if (head->token.aggregation.sign[0] == '<')
			{
				if (head->token.aggregation.word[0] == '-')
					close(!head->token.aggregation.n ? 0 : ft_atoi(head->token.aggregation.n));
				else
					dup2(!head->token.aggregation.n ? 0 : 
					ft_atoi(head->token.aggregation.n), ft_atoi(head->token.aggregation.word));
			}
			else
			{
				if (head->token.aggregation.word[0] == '-')
					close(!head->token.aggregation.n ? (*ast)->out : ft_atoi(head->token.aggregation.n));
				else
					dup2(!head->token.aggregation.n ? (*ast)->out : 
					ft_atoi(head->token.aggregation.n), ft_atoi(head->token.aggregation.word));
			}
		}
		head = head->next;
	}
}

void			visit_expression(t_ast_node *obj, t_ast **ast)
{
	t_ast_node		*left;
	t_ast_node		*right;

	left = obj->nodes.expr.left;
	right = obj->nodes.expr.right;
	left->node == 0 ? exec_factor(left, ast) : visit_expression(left, ast);
	right->node == 0 ? exec_factor(right, ast) : visit_expression(right, ast);
}