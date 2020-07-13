#include "lexer.h"
#include "parser_ast.h"

int		buildin_setenv(t_terminal *term, char **args)
{
	if (!args[1] || !args[2] || args[3])
		ft_printf("usage: setenv [key] [value]\n");
	else
	{
		set_key(term->env->linked, args[1], args[2]);
		free_table(term->env->table);
		term->env->table = update_enviroment(term->env->linked);
	}
	return (0);
}

int		buildin_unsetenv(t_terminal *term, char **args)
{
	if (!args[1] || args[2])
	{
		ft_printf("usage: unsetenv [key]\n");
		return (0);
	}
	unset_key(term->env->linked, args[1]);
	free_table(term->env->table);
	term->env->table = update_enviroment(term->env->linked);
	return (0);
}

int		buildin_env(char **env)
{
	ft_arriter(env, ft_putendl);
	return (0);
}
