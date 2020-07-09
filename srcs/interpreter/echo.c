#include "parser_ast.h"

void		buildin_echo(char **args)
{
	size_t	i;

	i = 0;
	while (args[++i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	exit(0);
}
