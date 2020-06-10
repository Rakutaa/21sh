#include "parser_ast.h"

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
		(*ast)->in = p[0];
		helper_close(obj, ast);
	}
}