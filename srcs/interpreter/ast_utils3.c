/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:02:46 by vtran             #+#    #+#             */
/*   Updated: 2020/06/10 18:51:58 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

/*
**adding redirection fd's
*/

void		do_redirection(t_ast **ast, t_redirection_aggregation *node)
{
	char						*file;
	char						*redir;

	file = node->node.t_redirection.file;
	redir = node->node.t_redirection.redir;
	if (redir[0] == '>')
	{
		close((*ast)->out);
		(*ast)->out = open(file, O_WRONLY | O_CREAT | (redir[1] == '\0' ?
		O_TRUNC : O_APPEND), S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
	}
	if (redir[0] == '<')
	{
		close((*ast)->in);
		(*ast)->in = open(file, O_RDONLY, O_CLOEXEC);
		dup2((*ast)->in, 0);
	}
}

void		do_aggregaation(t_redirection_aggregation *node)
{
	if (node->node.t_ag.sign[0] == '<')
	{
		if (node->node.t_ag.word[0] == '-')
			close(!node->node.t_ag.n ? 0 :
			ft_atoi(node->node.t_ag.n));
		else
		{
			close(0);
			dup2(!node->node.t_ag.n ? 0 : ft_atoi(node->node.t_ag.n),
			ft_atoi(node->node.t_ag.word));
		}
	}
	else
	{
		if (node->node.t_ag.word[0] == '-')
			close(!node->node.t_ag.n ? 1 : ft_atoi(node->node.t_ag.n));
		else
		{
			close(1);
			dup2(!node->node.t_ag.n ? 1 : ft_atoi(node->node.t_ag.n),
			ft_atoi(node->node.t_ag.word));
		}
	}
}


/*
**doing adding redirection or aggregation if some
*/

void		visit_factor(t_ast_node *obj, t_ast **ast)
{
	t_redirection_aggregation	*head;

	head = obj->nodes.t_factor.list;
	while (head)
	{
		if (head->e_flag == 0)
			do_redirection(ast, head);
		else if (head->e_flag == 1)
			do_aggregaation(head);
		head = head->next;
	}
}

void		exec_factor(t_ast_node *obj, t_ast **ast)
{
	int							p[2];
	pid_t						pid;

	pipe(p);
	pid = fork();
	if (pid == 0)
	{
		helper_dup(ast, obj, p[1]);
		close(p[0]);
		execvp(obj->nodes.t_factor.cmds[0], obj->nodes.t_factor.cmds);
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

/*
**right is actually always factor :D 
*/

void		visit_expression(t_ast_node *obj, t_ast **ast)
{
	t_ast_node					*left;
	t_ast_node					*right;

	left = obj->nodes.t_expr.left;
	right = obj->nodes.t_expr.right;
	left->e_node == 0 ? exec_factor(left, ast) : visit_expression(left, ast);
	right->e_node == 0 ? exec_factor(right, ast) : visit_expression(right, ast);
}
