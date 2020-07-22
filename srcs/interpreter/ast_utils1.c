/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:36:28 by vtran             #+#    #+#             */
/*   Updated: 2020/07/21 13:53:23 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

/*
**this is the substance of syntax grammar. 
**simple cmd.|| !ft_strcmp(str, "exit")
*/ 

int				is_buildin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd") || !ft_strcmp(str, "setenv")
	|| !ft_strcmp(str, "unsetenv") || !ft_strcmp(str, "env"))
		return (1);
	return (0);
}

static char			*path_join(char *str1, char *str2)
{
	size_t			i;
	char			*ret;

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

void			add_exec_path(char	*name, t_list *env, t_ast_node	*facto)
{
	char		**paths;
	char		*env_path_value;
	int			i;
	char		*path;

	if (access(name, F_OK) == 0)
	{
		facto->nodes.t_factor.path_join = ft_strdup(name);
		return ;
	}
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
	i = 0;
	while(paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

t_ast_node		*create_factor(char **cmnd, t_redirection_aggregation *list, t_list *env)
{
	t_ast_node	*facto;

	facto = malloc(sizeof(t_ast_node));
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

/*
**this is a pipe between two simple cmd
**left node write to pipe
**right node reads from pipe
*/

t_ast_node		*create_expression(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*express;

	express = malloc(sizeof(t_ast_node));
	express->e_node = EXPR;
	express->nodes.t_expr.left = left;
	express->nodes.t_expr.right = right;
	return (express);
}
