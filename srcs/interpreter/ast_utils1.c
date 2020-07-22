/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:36:28 by vtran             #+#    #+#             */
/*   Updated: 2020/07/23 00:40:29 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

int				is_buildin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd") ||
	!ft_strcmp(str, "setenv") || !ft_strcmp(str, "exit")
	|| !ft_strcmp(str, "unsetenv") || !ft_strcmp(str, "env"))
		return (1);
	return (0);
}

static char		*path_join(char *str1, char *str2)
{
	size_t		i;
	char		*ret;

	i = ft_strlen(str1);
	if (str1[i - 1] == '/')
		ret = ft_strjoin(str1, str2);
	else
	{
		str1 = ft_strjoin(str1, "/");
		ret = ft_strjoin(str1, str2);
		free(str1);
	}
	return (ret);
}

void			add_exec_path(char *name, t_list *env, t_ast_n *facto)
{
	char		**paths;
	char		*env_path_value;
	int			i;
	char		*path;

	if (access(name, F_OK) == 0)
		facto->nodes.t_factor.path_join = ft_strdup(name);
	if (access(name, F_OK) == 0)
		return ;
	i = -1;
	env_path_value = value_lookup(env, "PATH");
	if (!env_path_value)
		return ;
	paths = ft_strsplit(env_path_value, ':');
	while (paths[++i])
	{
		path = path_join(paths[i], name);
		if (access(path, F_OK) == 0)
		{
			facto->nodes.t_factor.path_join = path;
			break ;
		}
		free(path);
	}
	ft_arrfree(paths);
}

t_ast_n			*create_factor(char **cmnd, t_re_ag *list,
				t_list *env)
{
	t_ast_n		*facto;

	facto = malloc(sizeof(t_ast_n));
	facto->e_node = FACTOR;
	facto->nodes.t_factor.path_join = NULL;
	if (is_buildin(cmnd[0]))
		facto->nodes.t_factor.e_factor = BUILDIN;
	else
	{
		facto->nodes.t_factor.e_factor = EXEC;
		facto->nodes.t_factor.path_join = NULL;
		add_exec_path(cmnd[0], env, facto);
	}
	facto->nodes.t_factor.cmds = cmnd;
	facto->nodes.t_factor.list = list;
	return (facto);
}

t_ast_n			*create_expression(t_ast_n *left, t_ast_n *right)
{
	t_ast_n		*express;

	express = malloc(sizeof(t_ast_n));
	express->e_node = EXPR;
	express->nodes.t_expr.left = left;
	express->nodes.t_expr.right = right;
	return (express);
}
