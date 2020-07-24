/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:02:46 by vtran             #+#    #+#             */
/*   Updated: 2020/07/24 14:17:56 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

int			child(t_ast_n *obj, t_ast **ast, char **env)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if ((*ast)->parent->e_node == 1 && obj !=
		(*ast)->parent->nodes.t_expr.right)
			close((*ast)->pipe[0]);
		helper_dup(ast, obj, (*ast)->pipe[1]);
		if (obj->nodes.t_factor.e_factor == BUILDIN)
			!ft_strcmp(obj->nodes.t_factor.cmds[0], "echo") ?
			buildin_echo(obj->nodes.t_factor.cmds) :
			buildin_env(env);
		execve(obj->nodes.t_factor.path_join, obj->nodes.t_factor.cmds, env);
		abort();
	}
	return (pid);
}

void		visit_exec(t_ast_n *obj, t_ast **ast, char **env)
{
	if (obj->nodes.t_factor.e_factor == EXEC && !obj->nodes.t_factor.path_join)
		return (cmd_not_found(obj->nodes.t_factor.cmds[0]));
	if ((*ast)->parent->e_node == 1 && obj !=
	(*ast)->parent->nodes.t_expr.right)
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

void		visit_expression(t_ast_n *obj, t_ast **ast, t_terminal *term,
			t_free *willy)
{
	t_ast_n					*left;
	t_ast_n					*right;

	left = obj->nodes.t_expr.left;
	right = obj->nodes.t_expr.right;
	if (left->e_node == 0)
		left->nodes.t_factor.e_factor == 0 ?
		buildin_factor(left, ast, term, willy) :
		visit_exec(left, ast, term->env->table);
	else
		visit_expression(left, ast, term, willy);
	visit_exec(right, ast, term->env->table);
}
