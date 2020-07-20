#include "parser_ast.h"

void		buildin_echo(char **args)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	while (args[++i])
	{
		if (args[i][0] == '-')
		{
			if (args[i][1] == 'n')
			{
				flag = 1;
				continue ;
			}
		}
		else
		{
			ft_putstr(args[i]);
			if (args[i + 1])
			write(1, " ", 1);
		}
	}
	if (!flag)
		write(1, "\n", 1);
	exit(0);
}
