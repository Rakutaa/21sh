/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:02:46 by vtran             #+#    #+#             */
/*   Updated: 2020/07/21 15:01:52 by vkuokka          ###   ########.fr       */
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
	int							n;
	int							i;

	i= 0;
	file = node->node.t_redirection.file;
	redir = node->node.t_redirection.redir;
	if (ft_isdigit(redir[0]))
	{
		n = ft_atoi(redir);
		while(ft_isdigit(redir[i]))
			i++;
		if(redir[i] == '>')
		{
			if ((*ast)->out != 1)
				close((*ast)->out);
			(*ast)->out = open(file, O_WRONLY | O_CREAT | (redir[i + 1] == '\0' ?
		O_TRUNC : O_APPEND), S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
			dup2((*ast)->out, n);
			close((*ast)->out);
		}
		else if (redir[i] == '<' && redir[i + 1] == '>')
		{
			(*ast)->rwfd = open(file, O_RDWR| O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
			dup2((*ast)->rwfd, n);
			close((*ast)->rwfd);
		}
	}
	if (redir[0] == '&')
	{
		if ((*ast)->out != 1)
			close((*ast)->out);
		(*ast)->out = open(file, O_WRONLY | O_CREAT | 
		O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
		dup2((*ast)->out, 1);
		dup2((*ast)->out, 2);
		close((*ast)->out);
	}
	if (redir[0] == '>')
	{
		if ((*ast)->out != 1)
			close((*ast)->out);
		(*ast)->out = open(file, O_WRONLY | O_CREAT | (redir[1] == '\0' ?
		O_TRUNC : O_APPEND), S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
		dup2((*ast)->out, 1);
		close((*ast)->out);
	}
	if (redir[0] == '<' && !redir[1])
	{
		if ((*ast)->in != 0)
			close((*ast)->in);
		(*ast)->in = open(file, O_RDONLY);
		dup2((*ast)->in, 0);
		close((*ast)->in);
	}
	
	if (redir[0] == '<' && redir[1] == '<' && !redir[2])
	{
		if ((*ast)->in != 0)
			close((*ast)->in);
		(*ast)->in = node->node.t_redirection.heredoc[0];
		dup2((*ast)->in, 0);
		close((*ast)->in);
		close((node->node.t_redirection.heredoc[1]));
	}

	if (redir[0] == '<' && redir[1] == '>')
	{
		(*ast)->rwfd = open(file, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
		dup2((*ast)->rwfd, 0);
		close((*ast)->rwfd);
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
			if (fcntl(ft_atoi(node->node.t_ag.word), F_GETFL) == -1)
			{
				ft_printf("21sh bad fd, %s\n", node->node.t_ag.word);
				close(2);
			}
			else
				dup2(ft_atoi(node->node.t_ag.word), !node->node.t_ag.n ? 1 : ft_atoi(node->node.t_ag.n));
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
		else
			do_aggregaation(head);
		head = head->next;
	}
}

int			child(t_ast_node *obj, t_ast **ast, char **env)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if ((*ast)->parent->e_node == 1 && obj != (*ast)->parent->nodes.t_expr.right)
			close((*ast)->pipe[0]);
		helper_dup(ast, obj, (*ast)->pipe[1]);
		if (obj->nodes.t_factor.e_factor == BUILDIN)
			buildin_echo(obj->nodes.t_factor.cmds);
		execve(obj->nodes.t_factor.path_join, obj->nodes.t_factor.cmds, env);
		abort();
	}
	return (pid);
}

void		exec_factor(t_ast_node *obj, t_ast **ast, char **env)
{
	if (obj->nodes.t_factor.e_factor == EXEC && !obj->nodes.t_factor.path_join)
		return (cmd_not_found(obj->nodes.t_factor.cmds[0]));
	if ((*ast)->parent->e_node == 1 && obj != (*ast)->parent->nodes.t_expr.right)
		pipe((*ast)->pipe);
	(*ast)->pids[(*ast)->i] = child(obj, ast, env);
	(*ast)->i++;
	if ((*ast)->in != 0)
		close((*ast)->in);
	if ((*ast)->parent->e_node == 1 &&
	obj != (*ast)->parent->nodes.t_expr.right)
	{
		(*ast)->in = (*ast)->pipe[0];
		close((*ast)->pipe[1]);
	}
}
	// 	// 	if ((*ast)->in != 0)
	// 	// {
	// 	// 	dup2((*ast)->in, 0);
	// 	// 	close((*ast)->in);
	// 	// }
	// 	// if ((*ast)->parent->e_node == 1 &&
	// 	// obj != (*ast)->parent->nodes.t_expr.right)
	// 	// {
	// 	// 	dup2(p[1], 1);
	// 	// 	close(p[1]);
	// 	// }
	// else
	// {
	// 	// wait(NULL);
	// 	// close(p[1]);
	// 	// helper_close(obj, ast);
	// 	// (*ast)->in = p[0];
	// 	// if ((*ast)->parent->e_node == 0)
	// 	// 	close(p[0]);
	// 	// if ((*ast)->in != 0)
	// 	// 	close((*ast)->in);
	// 	// close(p[1]);
	// 	// (*ast)->in = p[0];
/*
**right is actually always factor :D 
*/

void		visit_expression(t_ast_node *obj, t_ast **ast, t_terminal *term)
{
	t_ast_node					*left;
	t_ast_node					*right;

	left = obj->nodes.t_expr.left;
	right = obj->nodes.t_expr.right;
	if (left->e_node == 0)
		left->nodes.t_factor.e_factor == 0 ? buildin_factor(left, ast, term) : exec_factor(left, ast, term->env->table);
	else
		visit_expression(left, ast, term);
	exec_factor(right, ast, term->env->table);
}
