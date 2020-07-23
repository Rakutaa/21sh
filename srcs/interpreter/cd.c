/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:06:33 by hege              #+#    #+#             */
/*   Updated: 2020/07/23 04:10:38 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"
#include "lexer.h"

static void		change_dir(t_env *enviroment, char *path)
{
	char		*value;
	char		absolute[ARG_MAX];

	if (access(path, F_OK) == -1)
		ft_dprintf(2, "cd: no such file or directory: %s\n", path);
	else if (access(path, X_OK) == -1)
		ft_dprintf(2, "cd: permission denied: %s\n", path);
	else if (chdir(path) == -1)
		ft_dprintf(2, "cd: not a directory: %s\n", path);
	else
	{
		value = value_lookup(enviroment->linked, "PWD");
		!value ? value = "" : 0;
		set_key(enviroment->linked, "OLDPWD", value);
		set_key(enviroment->linked, "PWD", getcwd(absolute, ARG_MAX));
		ft_arrfree(enviroment->table);
		enviroment->table = update_enviroment(enviroment->linked);
	}
}

int				buildin_cd(t_env *enviroment, char **args)
{
	char		*value;

	if (!args[1] || !args[1][0])
	{
		value = value_lookup(enviroment->linked, "HOME");
		!value ? ft_dprintf(2, "cd: HOME not set\n") \
		: change_dir(enviroment, value);
	}
	else if (args[2])
		ft_dprintf(2, "cd: too many arguments\n");
	else if (args[1][0] == '-' && !args[1][1])
	{
		value = value_lookup(enviroment->linked, "OLDPWD");
		if (!value)
			ft_dprintf(2, "cd: OLDPWD not set\n");
		else
		{
			ft_printf("%s\n", value);
			change_dir(enviroment, value);
		}
	}
	else
		change_dir(enviroment, args[1]);
	return (0);
}
