/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:02:46 by vtran             #+#    #+#             */
/*   Updated: 2020/07/24 16:00:34 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

int				child(t_ast_n *obj, t_ast **ast, char **env)
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
		if (execve(obj->nodes.t_factor.path_join, obj->nodes.t_factor.cmds, env)
		== -1)
			ft_dprintf(2, "21sh: permission denied: %s\n",
			obj->nodes.t_factor.cmds[0]);
		abort();
	}
	return (pid);
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

char			*add_exec_path(char *name, t_list *env)
{
	char		**paths;
	char		*env_path_value;
	int			i;
	char		*path;
	struct stat sta;

	if (ft_strrchr(name, '/'))
		return (if_slash(name));
	i = -1;
	env_path_value = value_lookup(env, "PATH");
	if (!env_path_value)
		return (NULL);
	paths = ft_strsplit(env_path_value, ':');
	while (paths[++i])
	{
		path = path_join(paths[i], name);
		stat(path, &sta);
		if (access(path, X_OK) == 0 && !S_ISDIR(sta.st_mode))
			break ;
		free(path);
		path = NULL;
	}
	ft_arrfree(paths);
	return (path);
}

void			visit_exec(t_ast_n *obj, t_ast **ast, t_env *env)
{
	obj->nodes.t_factor.path_join = add_exec_path(obj->nodes.t_factor.cmds[0],
	env->linked);
	if (obj->nodes.t_factor.e_factor == EXEC && !obj->nodes.t_factor.path_join)
		return (cmd_not_found(obj->nodes.t_factor.cmds[0]));
	if ((*ast)->parent->e_node == 1 && obj !=
	(*ast)->parent->nodes.t_expr.right)
		pipe((*ast)->pipe);
	(*ast)->pids[(*ast)->i] = child(obj, ast, env->table);
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

void			visit_expression(t_ast_n *obj, t_ast **ast, t_terminal *term,
			t_free *willy)
{
	t_ast_n					*left;
	t_ast_n					*right;

	left = obj->nodes.t_expr.left;
	right = obj->nodes.t_expr.right;
	if (left->e_node == 0)
		left->nodes.t_factor.e_factor == 0 ?
		buildin_factor(left, ast, term, willy) :
		visit_exec(left, ast, term->env);
	else
		visit_expression(left, ast, term, willy);
	visit_exec(right, ast, term->env);
}
