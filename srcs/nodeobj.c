#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

t_nodeobj		*mkfactor(char **cmnd, t_redirection *redirection)
{
	t_nodeobj		*facto;
	
	facto = malloc(sizeof(t_nodeobj));
	facto->node = factor;
	facto->nodes.factor.cmds = cmnd;
	facto->nodes.factor.redirection = redirection;
	return facto;
}

t_redirection	*mkredir(char *file, char *sign)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	redir->redir = sign;
	redir->file = file;
	redir->next = NULL;
	return redir;
}

t_nodeobj		*mkexpr(t_nodeobj *left, struct nodeobj *right)
{
	t_nodeobj *express;

	express = malloc(sizeof(t_nodeobj));
	express->node = expr;
	express->nodes.expr.left = left;
	express->nodes.expr.right = right;
	return express;
}

//>>

int			helper_create_file(char *file)
{
	pid_t	pid;
	char	*touch[] = {"touch", file, NULL};

	if (access(file, F_OK ) != -1 ) 
    // file exists
		return (open(file, O_WRONLY));
	else
	{
		// file doesn't exist
		pid = fork();
		if (pid == 0)
			execvp(touch[0], touch);
		wait(NULL);
		return (open(file, O_WRONLY));
	}
}

//helper aggreagation ?

// void			helper_aggregation(t_ast **ast)
// {

// }

void			helper_dup(t_ast **ast, t_nodeobj *obj, int pipe_in)
{
	dup2((*ast)->in, 0);
	if ((*ast)->parent->node == 1 && obj
	!= (*ast)->parent->nodes.expr.right)
		dup2(pipe_in, 1);
	else
		dup2((*ast)->out, 1);
}

//lisää vaihtoehtoja..

void			helper_close(t_nodeobj *obj, t_ast **ast)
{
	if (obj->nodes.factor.redirection)
	{
		if (obj->nodes.factor.redirection->redir[0] == '<')
			close((*ast)->in);
	}
}

void			exec_factor(t_nodeobj *obj, t_ast **ast)
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

void			visit_f(t_nodeobj *obj, t_ast **ast)
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
			(*ast)->out = redir[1] == '\0' ? 
			 open(file, O_WRONLY) : helper_create_file(file);
			 //make another rule if >>
		if (redir[0] == '<')
			(*ast)->in = open(file, O_RDONLY); //make another rule if <<
		head = head->next;
	}
	exec_factor(obj, ast);
}

void			visit_e(t_nodeobj *obj, t_ast **ast)
{
	t_nodeobj		*left;
	t_nodeobj		*right;

	left = obj->nodes.expr.left;
	right = obj->nodes.expr.right;
	left->node == 0 ? visit_f(left, ast) : visit_e(left, ast);
	right->node == 0 ? visit_f(right, ast) : visit_e(right, ast);
}

/*
**Usage:
**cobj = factor, pobj = pipe. 
**cobj sisältää t_redirectionin.
**jos on pipe niin se on vasen node. 
*/

// int main()
// {
//     t_nodeobj *cobj;
//     t_nodeobj *cobj2;
//     t_nodeobj *cobj3;

//     t_redirection *redir;

//     t_nodeobj *pobj;
//     t_nodeobj *pobj2;
    
//     t_ast     *ast;

//     char *ls[] = {"ls", "-al", NULL};
//     char *cat[] = {"cat", "-e", NULL};
//     char *nl[] = {"nl", NULL};
//     //char *grep[] = {"grep", "kakka", NULL};

//     redir = mkredir(strdup("file1"), strdup("<"));
//     t_redirection *redir2 = mkredir(strdup("kakka"), strdup(">>"));

//     cobj = mkfactor(ls, NULL);
//     cobj2 = mkfactor(nl, NULL);
//     cobj3 = mkfactor(cat, redir2);
//     //t_nodeobj *cobj4 = mkfactor(grep, redir);
//     //t_nodeobj *pobj3 = mkexpr(cobj4, cobj2);

//     pobj = mkexpr(cobj, cobj2);
//     pobj2 = mkexpr(pobj, cobj3);    
    
//     ast = malloc(sizeof(t_ast));
//     ast->parent = pobj2;
//     ast->in = 0;
//     ast->out = 1;
//     ast->err = 2;
//     ast->next = NULL;

//     while (ast)
//     {
//         switch(ast->parent->node) {
//             case factor:
//                 visit_f(ast->parent, &ast);
//                 break;
//             case expr:
//                 visit_e(ast->parent, &ast);
//                 break;
//         }
//     // ast->parent = cobj;
//     // ast->in= 0;
//     // ast->out = 1;
//     // ast->err = 2;
//     // exec_factor(cobj, &ast);
//         ast = ast->next;
//     }
//     return 0;
// }