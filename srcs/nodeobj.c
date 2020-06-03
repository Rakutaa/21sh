#include "parser_ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

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

//helper aggreagation ?

// void			helper_aggregation(t_ast **ast)
// {

// }

void			helper_dup(t_ast **ast, t_ast_node *obj, int pipe_in)
{
	dup2((*ast)->in, 0);
	if ((*ast)->parent->node == 1 && obj
	!= (*ast)->parent->nodes.expr.right)
		dup2(pipe_in, 1);
	else
		dup2((*ast)->out, 1);
}

//lisää vaihtoehtoja..

void			helper_close(t_ast_node *obj, t_ast **ast)
{
	if (obj->nodes.factor.redirection)
	{
		if (obj->nodes.factor.redirection->redir[0] == '<')
			close((*ast)->in);
	}
}

void			exec_factor(t_ast_node *obj, t_ast **ast)
{
	int			p[2];
	pid_t		pid;
		
	pipe(p);
	pid = fork();
	if (pid == 0)
	{
		helper_dup(ast, obj, p[1]);
		close(p[0]);
		execvp(obj->nodes.factor.cmds[0], obj->nodes.factor.cmds);
		exit(1);
	}
	else
	{
		wait(NULL);
		close(p[1]);
		helper_close(obj, ast);
		(*ast)->in = p[0];
	}
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