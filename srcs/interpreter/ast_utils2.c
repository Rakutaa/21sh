/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:39:26 by vtran             #+#    #+#             */
/*   Updated: 2020/07/23 04:09:12 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

void		buildin_factor(t_ast_n *obj, t_ast **ast, t_terminal *term,
			t_free *willy)
{
	if (!ft_strcmp(obj->nodes.t_factor.cmds[0], "cd"))
		buildin_cd(term->env, obj->nodes.t_factor.cmds);
	else if (!ft_strcmp(obj->nodes.t_factor.cmds[0], "echo"))
		visit_exec(obj, ast, term->env->table);
	else if (!ft_strcmp(obj->nodes.t_factor.cmds[0], "setenv"))
		buildin_setenv(term, obj->nodes.t_factor.cmds);
	else if (!ft_strcmp(obj->nodes.t_factor.cmds[0], "unsetenv"))
		buildin_unsetenv(term, obj->nodes.t_factor.cmds);
	else if (!ft_strcmp(obj->nodes.t_factor.cmds[0], "env"))
		buildin_env(term->env->table);
	else if (!ft_strcmp(obj->nodes.t_factor.cmds[0], "exit"))
		free_willy(willy, term);
}

void		execute_ast(t_ast *ast, t_terminal *term, t_free *willy)
{
	int		i;
	int		ret;

	while (ast)
	{
		i = 0;
		ast->pids = malloc(sizeof(int) * ast->cmds);
		if (ast->parent->e_node == FACTOR)
			ast->parent->nodes.t_factor.e_factor == BUILDIN ?
			buildin_factor(ast->parent, &ast, term, willy) :
			visit_exec(ast->parent, &ast, term->env->table);
		else
			visit_expression(ast->parent, &ast, term, willy);
		if (ast->cmds > 0)
		{
			while (i != ast->cmds)
			{
				waitpid(ast->pids[i], &ret, 0);
				i++;
			}
		}
		ast = ast->next;
	}
}

t_ast		*init_ast(void)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	ast->in = 0;
	ast->out = 1;
	ast->err = 2;
	ast->cmds = 0;
	ast->pids = NULL;
	ast->i = 0;
	ast->rwfd = -1;
	ast->pipe = malloc(sizeof(int) * 2);
	ast->parent = NULL;
	ast->next = NULL;
	return (ast);
}

/*
**either there is mulple cmds separated ; or first cmd
*/

t_ast		*create_ast_node(t_ast *ast, t_parser_l **list)
{
	if (!ast)
	{
		ast = init_ast();
		ast->parent = (*list)->parser_nodeobj->nodes.t_a.ast_nodeobj;
	}
	else if ((*list)->next)
	{
		ast->next = init_ast();
		ast->next->parent =
		(*list)->next->parser_nodeobj->nodes.t_a.ast_nodeobj;
		ast = ast->next;
		*list = (*list)->next;
	}
	*list = (*list)->next;
	return (ast);
}

/*
**ast->parent update. meaning that there is atleast one pipe
*/

t_ast		*create_ast_list(t_parser_l *list)
{
	t_ast	*ast;
	t_ast	*tmp;

	ast = NULL;
	tmp = ast;
	while (list)
	{
		if (list->parser_nodeobj->nodes.t_t.token->e_type != TOKEN_PIPE)
		{
			tmp = create_ast_node(tmp, &list);
			tmp->cmds++;
			if (!ast)
				ast = tmp;
		}
		else
		{
			tmp->parent = create_expression(tmp->parent,
			list->next->parser_nodeobj->nodes.t_a.ast_nodeobj);
			list = list->next->next;
			tmp->cmds++;
		}
	}
	return (ast);
}
